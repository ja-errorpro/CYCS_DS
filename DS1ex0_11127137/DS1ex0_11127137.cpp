// 11127137, 黃乙家
// If Chinese text cannot normally displays, please view this program with
// UTF-8.
/****************************************************/
/*  CPP Template for School                         */
/*  Author: CompileErr0r(YiJia)                     */
/*  Author ID: 11127137                             */
/*  Compile Environment: Windows 11 64bit MingW-GCC */
/*  Compiler: g++ 9.4                               */
/****************************************************/

#ifdef CONSTOPT

#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
// #pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")
#pragma comment(linker, "/stack:200000000")

#endif

// #include <bits/stdc++.h>

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <istream>
#include <iterator>
#include <list>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <valarray>
#include <vector>

using namespace std;
// speed up(Constant Optimize)
#define endl '\n'
// for more viewable
typedef unsigned long long ullong;
typedef pair<ullong, ullong> pUUL;

void WriteMenu() {
    // output menu to user

    cout << "\n***********************" << endl;
    cout << "*    DS homework 0    *" << endl;
    cout << "*-------Options-------*" << endl;
    cout << "*     0 : Exit        *" << endl;
    cout << "*1 : Task 1(iterative)*" << endl;
    cout << "*2 : Task 2(recursive)*" << endl;
    cout << "***********************" << endl;
    cout << "\n> ";
}

int InputNumber() {
    string Input;
    cout << "\nInput A Number > ";
    cin >> Input;

    try {
        int N = stoi(Input);
        return N;
    } catch (exception &e) {
        cout << "\nThis is an ILLEGAL input" << endl;
        return InputNumber();
    }

    return -1;
}
inline void Solve() { // task 1

    int N = InputNumber();
    ullong a = 0, b = 1, c = 1;
    // a = Fib(n-2), b = Fib(n-1), c = Fib(n)
    ullong outer_counter = 0;
    for (ullong rep = 1; rep <= N; ++rep, ++outer_counter) {
        if (a > ULLONG_MAX - b) { // if true, a+b will overflow <!>
            cout << "Stop here due to ULLONG overflow.\n";
            break;
        }
        c = a + b; // Fib(n) = Fib(n-1) + Fib(n-2)
        a = b;     // Memorize, keep a = F(n-2), b = F(n-1)
        b = c;

        ullong mindiff = c - 1, d1 = 1, d2 = c;
        ullong inner_counter = 0;

        for (ullong k = sqrt(c); k > 0; --k) {
            // find min(|divisor_1 - divisor_2|)
            // the pair should close to sqrt(c)
            ++inner_counter;
            if (c % k == 0) { // k is one of the divisors

                ullong diff = (k > c / k ? k - c / k : c / k - k);
                // diff = | k - c/k |, |x| means absolute value (abs())
                if (diff < mindiff) {
                    // update min value
                    d1 = k;
                    d2 = c / k;
                    // d1 * d2 == c
                    mindiff = diff;
                    break;
                }
            }
        }

        cout << "[" << setw(3) << rep << "] " << c << " = " << d1 << " * " << d2 << "\t"
             << "(Inner loop:" << setw(10) << inner_counter << " times)" << endl;
    }

    cout << setw(3) << "<Outer loop:" << setw(10) << outer_counter - 1 << " times>" << endl;
}

void FindClosestDivisor(ullong k, ullong &x1, ullong &x2, ullong &target, ullong &mindiff,
                        ullong &recur_counter) {
    if (k == 0) // bound condition
        return;
    ++recur_counter;
    if (target % k == 0) { // k is one of the divisors
        int tmp = target / k;
        int diff = (k > tmp ? k - tmp : tmp - k);
        // diff = | k - tmp | = abs(k - tmp)

        if (diff < mindiff) {
            // update minimum and divisors
            mindiff = diff;
            x1 = k;
            x2 = target / k;
            return;
        }
    }
    FindClosestDivisor(k - 1, x1, x2, target, mindiff, recur_counter);
}

pUUL F(ullong n,
       ullong &recur_counter) { // F(n) = {Fib(n-1), Fib(n-2)} =
                                // F(n-1).first + F(n-1).second
    ++recur_counter;
    ullong inner_counter = 0;
    ullong d1 = 1, d2 = n, mindiff = d2 - d1;
    if (n <= 1) { // bound condition
        cout << "[" << setw(3) << n << "] ";
        cout << n << " = ";

        FindClosestDivisor(sqrt(n), d1, d2, n, mindiff, inner_counter);
        cout << d1 << " * " << d2 << "\t"
             << "(Inner recursion:";
        cout << setw(10) << inner_counter << " times)" << endl;
        return make_pair(n, 1); // Fib(1) = 1
    }

    pUUL pre = F(n - 1, recur_counter);        // {F(n-1), F(n-2)}
    if (pre.first > ULLONG_MAX - pre.second) { // if true, pre.first + pre.second will overflow <!>
        cout << "Stop due to overflow." << endl;
        return pre;
    }

    pUUL ret = {pre.first + pre.second, pre.first}; // {Fib(n), Fib(n-1)}
    cout << "[" << setw(3) << n << "] ";

    cout << ret.first << " = ";
    d2 = ret.first;
    mindiff = d2 - d1;
    FindClosestDivisor(sqrt(ret.first), d1, d2, ret.first, mindiff, inner_counter);

    cout << d1 << " * " << d2 << "\t"
         << "(Inner recursion:";
    cout << setw(10) << inner_counter << " times)" << endl;

    return ret;
}
inline void Solve2() { // task 2

    int N = InputNumber();
    ullong Outer_Counter = 0;
    F(N, Outer_Counter);
    cout << setw(3) << "<Outer recursion:" << setw(10) << Outer_Counter << " times>" << endl;
}
int main() {
    string command;
    // use string to avoid malicious input
    WriteMenu();
    while (cin >> command && command != "0") {
        if (command == "1")
            Solve();
        else if (command == "2")
            Solve2();
        else
            cout << "\nCommand does not Exist!!!" << endl;
        WriteMenu();
    }

    // Uncomment below line to measure time
    // cerr << "Time: " << (double)clock() / (double)CLOCKS_PER_SEC << '\n';

    return 0;
}
