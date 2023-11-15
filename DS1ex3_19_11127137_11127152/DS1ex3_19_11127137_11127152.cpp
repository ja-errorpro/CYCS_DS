// 11127137, 黃乙家, 11127152 郭怡楨
/****************************************************/
/*  CPP Template for School                         */
/*  Author: CompileErr0r(YiJia)                     */
/*  Author ID: 11127137                             */
/*  Compile Environment: Linux 5.15.90.1 WSL x86_64 */
/*  Compiler: g++ 9.4                               */
/****************************************************/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <new>

// #include <bits/stdc++.h>
using namespace std;

#define endl '\n'

template <class T>
class Queue {};

class Data {};

class Solution {};
void WriteMenu();
inline void Solve();
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
