#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <string>
#include <fstream>

using namespace std;

class Solution {
private:
    int * visited;
    int t;
    int s;
    int * mem;

    void dfs1(vector<int> G[], int& i) {
        visited[i] = 1;
        for(auto it = begin(G[i]); it != end(G[i]); ++it)
            if( !visited[*it] ) dfs1(G,*it);
        ++t;
        mem[i] = t; // finish times
    }

    void dfs2(vector<int> G[], int& i) {
        visited[i] = 1;
        mem[i] = s; // leader
        for(auto it = begin(G[i]); it != end(G[i]); ++it)
            if( !visited[*it] ) dfs2(G,*it);
    }

public:
    void findSCCs(int n, vector<vector<int>>& edges) {
        // nodes are 1indexed !!!

        // visited tracking
        visited = new int[n+1];

        // pass1: finish times, pass2: leader
        mem = new int[n+1];

        // edges -> adjacency list == our Graph
        vector<int> * G = new vector<int>[n+1];
        // init Graph
        for(int i = 0; i <= n; ++i)
            G[i] = {};
        
        // 1ST PASS FOR REVERSED GRAPH
        
        auto N = edges.size();
        // cout << "N " << N << endl;
        // debug
        // for(int i = 0; i < N; ++i)
        //     cout << edges[i][0] << " " << edges[i][1] << endl;

        for(int i = 0; i < N; ++i)
            G[edges[i][1]].push_back(edges[i][0]); // reversing edges

        // init visited
        for(int i = 0; i <= n; ++i)
            visited[i] = 0;

        t = 0;
        for(int i = n; i >= 1; --i)
            if( !visited[i] ) {
                dfs1(G,i);
            }

        // debug
        // cout << "finishing times" << endl;
        // for(int i = 1; i <= n; ++i)
        //    cout << i << " " << mem[i] << endl;;

        // 2ND PASS FOR ORIGINAL GRAPH in the order of finishing times
        
        // reset Graph
        for(int i = 0; i <= n; ++i)
            G[i].clear();
        
        for(int i = 0; i < N; ++i) {
            // debug
            // cout << "org edge " << edges[i][0] << " " << edges[i][1] << endl;
            // cout << "new edge " << mem[edges[i][0]] << " " << mem[edges[i][1]] << endl;

            G[mem[edges[i][0]]].push_back(mem[edges[i][1]]); // renaming nodes
        }

        // reset visited
        for(int i = 0; i <= n; ++i)
            visited[i] = 0;

        t = 0;
        for(int i = n; i >= 1; --i)
            if( !visited[i] ) {
                //cout << i << endl;
                s = i;
                dfs2(G,i);
            }
        
        // debug
        // cout << "leaders" << endl;
        // for(int i = 1; i <= n; ++i)
        //     cout << i << " " << mem[i] << endl;;

        // output size of the 5 largests sccs
        unordered_map<int,int> sccs;
        for(int i = 1; i <= n; ++i) {
            auto p = sccs.insert({mem[i],1}); // leader
            if( !p.second ) ++p.first->second;
        }
        
        //cout << "map" << endl;
        //for(auto it = begin(sccs); it != end(sccs); ++it) {
        //    cout << it->first << " " << it->second << endl;
        //}
        
        // dump map to vector to sort by val
        vector<int> v;
        for(auto it = begin(sccs); it != end(sccs); ++it)
            v.push_back(it->second);
        sort(begin(v),end(v),greater<int>());

        string r = to_string(v[0]);
        int i = 1;
        for(; i < v.size(); ++i) {
            if( i > 4 ) break;
            r += "," + to_string(v[i]);
        }
        while( i < 5 ) {
            r += ",0";
            ++i;
        }

        cout << r << endl;


        delete[] visited;
        delete[] mem;
        delete[] G;
    }
};

int main(int argc, char** argv) {

    // expect number of verticies space filename
    // UPDATE: expect file name only

    Solution s;
    vector<vector<int>> edges;

    // edges = {{1,5},{2,3},{3,4},{4,2},{4,5},{5,6},{6,1},{6,9},{7,8},{8,9},{9,7}};

    // reversed graph
    // edges = {{1,7},{2,5},{3,9},{4,1},{5,8},{6,3},{6,8},{7,9},{7,4},{8,2},{9,6}};

    // original graph
    // edges = {{1,4},{2,8},{3,6},{4,7},{5,2},{6,9},{7,1},{8,5},{8,6},{9,3},{9,7}};

    ifstream sccFile;
    string a;
    string b;
    set<int> e;

    // string n = argv[1];
    // string fn = argv[2];
    string fn = argv[1];

    //sccFile.open("SCC.txt"); // 875714 vertices
    //sccFile.open("SCCExample.txt"); // 9 verticies
    sccFile.open(fn);
    while(sccFile >> a >> b) {
        vector<int> edge;
        edge.push_back(stoi(a));
        e.insert(stoi(a));
        edge.push_back(stoi(b));
        e.insert(stoi(b));
        edges.push_back(edge);
        // cout << a << " " << b << "a" << endl;
    }
    sccFile.close();

    //s.findSCCs(875714,edges);
    //s.findSCCs(9,edges);
   
    cout << "min node  " << *e.begin() << endl;
    cout << "max node  " << *e.rbegin() << endl;
    cout << "nbr nodes " << e.size() << endl;
    cout << "nrb edges " << edges.size() << endl;    

    

    // s.findSCCs(stoi(n),edges);
    s.findSCCs(*e.rbegin(),edges);


    return 0;
}
