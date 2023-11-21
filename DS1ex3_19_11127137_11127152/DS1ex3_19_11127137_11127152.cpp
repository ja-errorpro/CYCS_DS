// 11127137, 黃乙家, 11127152 郭怡楨
/****************************************************/
/*  CPP Template for School                         */
/*  Author: CompileErr0r(YiJia)                     */
/*  Author ID: 11127137                             */
/*  Compile Environment: Linux 5.15.90.1 WSL x86_64 */
/*  Compiler: g++ 9.4                               */
/****************************************************/

#include <chrono>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <new>
#include <vector>

// #include <bits/stdc++.h>
using namespace std;

#define endl '\n'

template <class T>
class Queue {};

class Data {
   public:
    struct Process {
        int OID, Arrival, Duration, Timeout;
        bool operator<(const Process &p) const {
            if (Arrival == p.Arrival) {
                return OID < p.OID;
            }
            return Arrival < p.Arrival;
        }
    };
    struct Process_State {
        int OID, Finish, Delay;
    };

   public:
    static void shellsort(vector<Process> &p) {
        int n = p.size();
        for (int gap = n / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < n; i++) {
                Process temp = p[i];
                int j;
                for (j = i; j >= gap; j -= gap) {
                    // a[j]=a[j-gap];
                    if (temp < p[j - gap]) {
                        p[j] = p[j - gap];
                    } else {
                        break;
                    }
                }
                p[j] = temp;
            }
        }
    }
};

class Solution {
    typedef Data::Process Process;
    typedef Data::Process_State Process_State;
    vector<Process> ProcessList;
    vector<Process_State> Success;
    vector<Process_State> Fail;
    int64_t Read_Time;
    int64_t Sort_Time;
    int64_t Write_Time;

   public:
    void Case1() {
        string filename;
        ifstream fp;
        ofstream fout;
        do {
            cout << "Input a file name or file number >";
            cin >> filename;
            if (filename.size() == 3) {
                filename = "input" + filename + ".txt";
                fp.open(filename.c_str());
                if (!fp.is_open()) {
                    cout << "\nNo such file..." << endl;
                }
            } else if (!fp.is_open()) {
                cout << "\nNo such file..." << endl;
            }
        } while (!fp.is_open());
        fout.open("sorted" + filename.substr(5, 3) + ".txt");
        chrono::steady_clock::time_point start = chrono::steady_clock::now();
        string sch;
        for (int i = 0; i < 4; ++i) {
            fp >> sch; // read the first row
        }
        int n = 0;

        while (fp >> sch) {
            Process o;
            o.OID = stoi(sch);
            fp >> o.Arrival >> o.Duration >> o.Timeout;
            ProcessList.push_back(o);
            n++;
        }
        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        Read_Time = chrono::duration_cast<chrono::microseconds>(end - start).count();
        start = chrono::steady_clock::now();
        Data::shellsort(ProcessList);
        end = chrono::steady_clock::now();
        Sort_Time = chrono::duration_cast<chrono::microseconds>(end - start).count();
        start = chrono::steady_clock::now();
        fout << "OID\tArrival\tDuration\tTimeout" << endl;
        for (int i = 0; i < n; ++i) {
            fout << ProcessList[i].OID << '\t' << ProcessList[i].Arrival << '\t' << ProcessList[i].Duration
                 << '\t' << ProcessList[i].Timeout << endl;
        }
        end = chrono::steady_clock::now();
        Write_Time = chrono::duration_cast<chrono::microseconds>(end - start).count();

        cout << "Reading Time: " << Read_Time << " us" << endl;
        cout << "Sorting Time: " << Sort_Time << " us" << endl;
        cout << "Writing Time: " << Write_Time << " us" << endl;
        fp.close();
        fout.close();
    }
};
void WriteMenu() {
    cout << "1. Case1" << endl;
    cout << "0. Exit" << endl;
    cout << ">";
}
signed main() {
    string command;
    Solution s;
    // use string to avoid malicious input
    WriteMenu();
    while (cin >> command && command != "0") {
        cin.ignore();
        if (command == "1") {
            s.Case1();
            // cerr << "\033[1;32mTask Passed\033[0m" << endl;
        } else
            cout << "\nCommand does not Exist!!!" << endl;
        WriteMenu();
    }
    // cerr << "Time: " << (double)clock() / (double)CLOCKS_PER_SEC << '\n';
    return 0;
}
