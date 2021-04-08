#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <array>
#include <queue>

using namespace std;

class Solution {
private:


public:
    void shortestPath(int n, vector<array<int,3>>& edges, int s) {

        // edges -> adjacency list == our undirected weighted Graph
        // vector<array<int,2>> * G = new vector<array<int,2>>[n+1];
        vector<array<int,2>> G[n+1];
        auto N = edges.size();
        for(int i = 0; i < N; ++i) {
            G[edges[i][0]].push_back({edges[i][1],edges[i][2]});
            G[edges[i][1]].push_back({edges[i][0],edges[i][2]});
        }

        // min heap
        priority_queue<array<int,2>,vector<array<int,2>>,greater<array<int,2>>> pq;

        // distances
        int A[n+1];
        for(int i = 0; i < n+1; ++i) A[i] = 1000000;

        // push our source vertex into priority queue 
        pq.push({0,s});
        // set distance to our source vertex itself to 0
        A[s] = 0;

        while(!pq.empty()) {

            int u = pq.top()[1];
            pq.pop();
  
            vector<array<int,2>>::iterator it; 
            for(it = G[u].begin(); it != G[u].end(); ++it) { 
                int v = (*it)[0]; 
                int weight = (*it)[1]; 
  
                //  If there is shorted path to v through u. 
                if( A[v] > A[u] + weight ) { 
                    // Updating distance of v 
                    A[v] = A[u] + weight; 
                    pq.push({A[v], v}); 
                } 
            } 
        }

        // delete[] G;

        for(int i = 0; i < n+1; ++i)
            cout << i << " " << A[i] << endl;

        vector<int> distidx = {7,37,59,82,99,115,133,165,188,197};
        for(auto it = distidx.begin(); it != distidx.end(); ++it) {
            if( it != distidx.begin()) cout << ",";
            cout << A[*it];
        }
        cout << endl;



    }
};

int main(int argc, char** argv) {

    // file to process
    // string fn = argv[1];

    // ifstream file("dijkstraDataExample.txt");
    ifstream file("dijkstraData.txt");
    string line,token;
    vector<array<int,3>> edges;
    set<int> e; // track unique labels
    int sp,a,b,dis;
    while(getline(file, line)) {
        // cout << "line " << line << endl;

        // assum vertices are labeled 1 to n
        a = -1;
        istringstream iss(line);
        while(getline(iss, token, '\t')) {
            // cout << token << endl;
            if( a == -1 ) {
                a = stoi(token);
                e.insert(a);
                continue;
            }

            // lines end with another tab, hence check for npos
            sp = token.find(',');
            if( sp == string::npos ) continue;

            b = stoi(token.substr(0,sp));
            dis = stoi(token.substr(sp+1));

            e.insert(b);
            // cout << a << " " << b << " " << dis << endl;
            edges.push_back({a,b,dis});
            edges.push_back({b,a,dis});
        }
    }

    // debug
    cout << "min node  " << *e.begin() << endl;
    cout << "max node  " << *e.rbegin() << endl;
    cout << "nbr nodes " << e.size() << endl;
    cout << "nbr edges " << edges.size()/2 << endl;    
    // for(auto edge : edges) {
    //     cout << edge[0] << " " << edge[1] << " " << edge[2] << endl;
    // }


    Solution s;
    s.shortestPath(*e.rbegin(),edges,1);



    // TODO
    // report the shortest-path distances to the following ten vertices
    // in order: 7,37,59,82,99,115,133,165,188,197



    return 0;
}
