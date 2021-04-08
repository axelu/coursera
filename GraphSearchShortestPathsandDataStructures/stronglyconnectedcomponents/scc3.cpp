#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>




using namespace std;

class Solution {
private:
    int * pVisited;
    int t;
    int s;
    int * pLeader;
    int * pFinishTimes;

    void dfs(vector<int> G[], int i) {
        // cout << i << endl;
        pVisited[i] = 1;
        pLeader[i] = s;
        vector<int> edges = G[i];
        for(auto it = begin(edges); it != end(edges); ++it)
            if( !pVisited[*it] ) dfs(G,*it);
        ++t;
        pFinishTimes[i] = t;
    }
public:
    void findSCCs(int n, vector<vector<int>>& edges) {
        // nodes are 1indexed !!!

        // visited tracking
        int visited[n+1];
        pVisited = visited;

        // leader tracking
        int leader[n+1];
        pLeader = leader;

        // finish time tracking
        int finishTimes[n+1];
        pFinishTimes = finishTimes;

        // 1ST PASS FOR REVERSED GRAPH
        // edges -> adjacency list
        vector<int> Grev[n+1];
        auto N = edges.size();
        for(int i = 0; i < N; ++i)
            Grev[edges[i][1]].push_back(edges[i][0]); // reversing edges

        // init visited
        for(int i = 0; i <= n; ++i)
            visited[i] = 0;

        t = 0;
        for(int i = n; i >= 1; --i)
            if( !visited[i] ) {
                s = i;
                dfs(Grev,i);
            }

        // 2ND PASS FOR ORIGINAL GRAPH in the order of finishing times
        vector<int> G[n+1];
        for(int i = 0; i < N; ++i)
           G[finishTimes[edges[i][0]]].push_back(finishTimes[edges[i][1]]); // renaming nodes

        // reset visited
        for(int i = 0; i <= n; ++i)
            visited[i] = 0;

        t = 0;
        for(int i = n; i >= 1; --i)
            if( !visited[i] ) {
                s = i;
                dfs(G,i);
            }

        cout << "leaders" << endl;
        for(int i = 1; i <= n; ++i)
            cout << i << " " << leader[i] << endl;;

        // output size of the 5 largests sccs
        unordered_map<int,int> sccs;
        for(int i = 1; i <= n; ++i) {
            auto p = sccs.insert({leader[i],1});
            if( !p.second ) ++p.first->second;
        }
        cout << "map" << endl;
        for(auto it = begin(sccs); it != end(sccs); ++it) {
            cout << it->first << " " << it->second << endl;
        }
        // dump map to vector to sort by val
        vector<int> v;
        for(auto it = begin(sccs); it != end(sccs); ++it)
            v.push_back(it->second);
        sort(begin(v),end(v),greater<int>());

        string r = to_string(v[0]);
        int i = 1;
        for(; i < v.size(); ++i)
            r += "," + to_string(v[i]);
        while( i < 5 ) {
            r += ",0";
            ++i;
        }

        cout << r << endl;

    }
};

int main() {

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

    sccFile.open("SCCExample.txt");
    while(sccFile) {
        sccFile >> a >> b;
        vector<int> edge;
        edge.push_back(stoi(a));
        edge.push_back(stoi(b));
        edges.push_back(edge);
        // cout << a << " " << b << "a" << endl;
    }
    sccFile.close();



    s.findSCCs(9,edges);

    return 0;
}
