#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <set>
#include <optional>

using namespace std;

long long arr[1000000];
set<long long> s;

optional<pair<long long,long long>> twosum(int t) {
    long long diff;
    set<long long>::iterator se = s.end();
    for(int i = 0; i < 1000000; ++i) {
        diff = (long long)t - arr[i];
        if( diff != arr[i] && s.find(diff) != se ) {
            optional<pair<long long,long long>> o = make_pair(arr[i],diff);
            return o;
        }
    }
    return nullopt;
}

int main() {

    ifstream file("algo1-programming_prob-2sum.txt");
    string line;
    int i = 0;
    long long v;
    while(getline(file,line)) {
        v = stoll(line); 
        arr[i] = v;
        s.insert(v);
        ++i;
    }

    // debug
    // for(i = 0; i < 1000000; ++i)
    //   cout << i << " " << arr[i] << endl;
    
    int r = 0;
    for(i = -10000; i <= 10000; ++i) {
        cout << "trying target " << i << endl;
        if( twosum(i) ) ++r;
    }

    cout << r << endl;

    return 0;
}
