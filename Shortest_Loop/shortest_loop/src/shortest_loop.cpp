#include "shortest_loop.h"
#include <iostream>
#include <queue>

using namespace std;

shortest_loop::shortest_loop()
{
    //ctor
}

void shortest_loop::add_edge(int u,int v,int weight){
    socket_list.push_back(Socket(u,Edge(u,v,weight)));
    socket_list.push_back(Socket(v,Edge(v,u,weight)));
    node_adj[u].push_back(socket_list.size() - 2);
    node_adj[v].push_back(socket_list.size() - 1);
}

shortest_loop::shortest_loop(string filename){
    freopen(filename.c_str(),"r",stdin);
    cin >> node_num;
    cin >> edge_num;
    socket_list.clear();
    for (int i = 0;i <= node_num;i++)
        node_adj[i].clear();
    for (int i = 1;i <= edge_num;i++){
        int u,v,weight;
        cin >> u >> v >> weight;
        add_edge(u,v,weight);
    }

    #ifdef DEBUG
    cout << "all the sockets are" << endl;
    for (int i = 0;i < socket_list.size();i++){
        cout << socket_list[i].node_id << " " << socket_list[i].edge.from << " " << socket_list[i].edge.to << endl;
    }
    #endif
}

shortest_loop::~shortest_loop()
{
    //dtor
}

void shortest_loop::Dijsktra(int start,int cut_off,vector<int>& ans,int& mini_composite_distance){

    #ifdef DEBUG
    cout << endl;
    cout << "the start node now is " << start << endl;
    #endif // DEBUG

    priority_queue<queue_node>Heap;

    while(!Heap.empty()) Heap.pop();

    for (int i = 0;i < socket_list.size();i++)
        if (socket_list[i].node_id == start)
            Heap.push(queue_node(i,socket_list[i].edge.distance));

    ans.clear();
    mini_composite_distance = ~0U>>1;
    for (int i = 1;i <= node_num;i++)
        walk[i].clear();

    for (int i = 1;i <= node_num;i++)
        walk[i].insert(i);

    memset(visit,0,sizeof(visit));

    while(!Heap.empty()){

        queue_node now_node = Heap.top(); Heap.pop();
        if (now_node.distance > cut_off) return;
        int s_id = now_node.socket_id;
        if (visit[s_id]) continue;
        visit[s_id] = 1;
        int source = socket_list[s_id].node_id;
        int to = socket_list[s_id].edge.to;

        #ifdef DEBUG
        cout << "now_socket is " << source << " --> " << to;
        cout << ", the distance is " << now_node.distance << endl;
        #endif // DEBUG

        if (walk[source].find(to) != walk[source].end()){
            set<int>::iterator it;
            for (it = walk[source].begin();it != walk[source].end();it++)
                ans.push_back((*it));
            mini_composite_distance = now_node.distance;

            #ifdef DEBUG
            cout << ans.size() << endl;
            for (int i = 0;i < ans.size();i++)
                cout << ans[i] << " ";
            cout << endl;
            #endif // DEBUG
            return;
        }

        for (int i = 0;i < node_adj[to].size();i++){
            int next_socket_id = node_adj[to][i];
            int next_node = socket_list[next_socket_id].edge.to;
            if (next_node == socket_list[s_id].node_id) continue;
            int now_dist = now_node.distance + socket_list[next_socket_id].edge.distance;
            if (now_dist > cut_off) continue;
            int now_node = socket_list[next_socket_id].node_id;
            set<int>::iterator it;
            for (it = walk[source].begin();it != walk[source].end();it++)
                walk[now_node].insert((*it));
            walk[now_node].insert(now_node);
            Heap.push(queue_node(next_socket_id,now_dist));
        }
    }
}

void shortest_loop::find_loops(vector<vector<int> >&loops){
    int cut_off = ~0U>>1;
    vector<int>tmp;
    loops.clear();
    memset(used,0,sizeof(used));
    for (int i = 1;i <= node_num;i++){
        tmp.clear();
        int mdst;
        Dijsktra(i,cut_off,tmp,mdst);
        for (int i = 0;i < tmp.size();i++)
            used[tmp[i]] = 1;
        if (cut_off > mdst) loops.clear();
        cut_off = min(cut_off,mdst);
        if (cut_off == mdst){
            loops.push_back(tmp);
        }
    }
}
