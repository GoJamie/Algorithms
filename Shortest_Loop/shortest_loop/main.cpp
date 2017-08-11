#include <iostream>
#include "include\shortest_loop.h"

using namespace std;


int main()
{

    shortest_loop* solver = new shortest_loop("C:/Repository/CV/Code/Algorithms/Shortest_Loop/shortest_loop/data/test1.in");
    vector<vector<int> >ans;
    solver->find_loops(ans);
    for (int i = 0;i < ans.size();i++){
            for (int j = 0;j < ans[i].size();j++)
                cout << ans[i][j] << " ";
            cout << endl;
    }
    return 0;
}
