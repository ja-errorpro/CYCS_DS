// 11127137 ¶À¤A®a   11127152 ³¢©É·©

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <new>

using namespace std;

#define endl '\n'

class Data {

} ;

class Solution {

};

void WriteMenu();

void Solve();

signed main() {
    string command;

    // use string to avoid malicious input
    WriteMenu();
    while (cin >> command && command != "0") {
        cin.ignore();
        if (command == "1") {
            Solve();
            // cerr << "\033[1;32mTask Passed\033[0m" << endl;
        } else
            cout << "\nCommand does not Exist!!!" << endl;
        WriteMenu();
    }
    // cerr << "Time: " << (double)clock() / (double)CLOCKS_PER_SEC << '\n';
    return 0;
}
