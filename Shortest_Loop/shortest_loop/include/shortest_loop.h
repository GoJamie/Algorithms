#ifndef SHORTEST_LOOP_H
#define SHORTEST_LOOP_H
#include <vector>
#include <iostream>
#include <fstream>
#include <set>
#include <cstring>
#include <string>

const int MAX_NODE_NUM = 51000;

struct Edge{
    int from,to;
    int distance;
    Edge(int _from,int _to,int _weight):from(_from),to(_to),distance(_weight){}
    Edge(){}
};

struct Socket{
    int node_id;
    Edge edge;
    Socket(int id,const Edge& e){
        node_id = id;
        edge = e;
    }
};

struct queue_node{
    int socket_id;
    int distance;
    queue_node(int _id,int _dis):socket_id(_id),distance(_dis){}
    bool operator<(const queue_node& qnode)const{
        return distance < qnode.distance;
    }
};

class shortest_loop
{
    public:
        shortest_loop();
        shortest_loop(std::string filename);
        virtual ~shortest_loop();
        void find_loops(std::vector<std::vector<int> >& loops);
    protected:
    private:
        std::vector<Socket>socket_list;
        void add_edge(int u,int v,int weight);
        int node_num,edge_num;
        std::vector<int>node_adj[MAX_NODE_NUM];
        bool visit[MAX_NODE_NUM];
        bool used[MAX_NODE_NUM];
        void Dijsktra(int start,int cut_off,std::vector<int>& ans,int mini_composite_distance);
        std::set<int>walk[MAX_NODE_NUM];
};



#endif // SHORTEST_LOOP_H
