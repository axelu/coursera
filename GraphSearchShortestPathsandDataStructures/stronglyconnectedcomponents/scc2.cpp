#include <iostream>
#include <fstream>

using namespace std;

int main() {

    ifstream sccFile;
    string a;
    string b;

    sccFile.open("SCCExample.txt");
    while(sccFile) {
        sccFile >> a >> b;
        cout << a << " " << b << "a" << endl;
    }
    sccFile.close();





    return 0;
}
