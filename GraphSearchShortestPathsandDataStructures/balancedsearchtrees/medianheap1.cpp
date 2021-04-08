#include <iostream>
#include <fstream>
#include <string>
#include <queue>

using namespace std;

int arr[10000];
int MOD = 10000;

int medianMaintenance() {
    // max heap, stores the smaller half elements, left side
    priority_queue<int> l; 
  
    // min heap, stores the greater half elements, right side 
    priority_queue<int,vector<int>,greater<int> > r; 

    // init
    int m = arr[0]; 
    int ans = arr[0];
    l.push(arr[0]); 

    for(int i = 1; i < 10000; ++i) { 
        int k = arr[i]; 
  
        if( l.size() > r.size() ) { 
            // case 1: left side heap has more elements 
            if( k < m ) { 
                r.push(l.top()); 
                l.pop(); 
                l.push(k); 
            } else {
                r.push(k); 
            }
            // now even
            // m = (l.top() + r.top())/2.0;
            m = l.top();
        } else if( l.size() == r.size() ) { 
            // case 2: left an right heaps are balanced
            if( k < m ) { 
                l.push(k); 
                m = l.top(); 
            } else { 
                r.push(k); 
                m = r.top(); 
            } 
        } else {
            // case 3: right side heap has more elements
            if( k > m ) { 
                l.push(r.top()); 
                r.pop(); 
                r.push(k); 
            } else {
                l.push(k); 
            }
            // now even
            // m = (l.top() + r.top())/2.0; 
            m = l.top();
        }
        ans = ((ans % MOD) + (m % MOD)) % MOD;
    }
    return ans;
}

int main() {

    ifstream file("Median.txt");
    string line;
    int i = 0;
    while(getline(file,line)) {
        arr[i] = stoi(line);
        ++i;
    }

    // debug
    // for(i = 0; i < 10000; ++i)
    //    cout << i << " " << arr[i] << endl;


    cout << medianMaintenance() << endl;

    return 0;
}
