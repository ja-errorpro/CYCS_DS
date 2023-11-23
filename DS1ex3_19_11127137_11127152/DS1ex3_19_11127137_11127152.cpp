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
const int queueMax = 3;

template <class T>
class Queue {
    vector<T> q;

   public:
    int length() const { // get the current queue length
        return q.size();
    }

    bool isEmpty() const { // check whether it is empty
        return q.empty();
    }

    bool isFull() const { // check whether it is full
        return q.size() >= queueMax;
    }

    void push(const T &input) { // add the new element at last
        q.push_back(input);
    }

    void getFront(T &first) { // get the first element
        first = q.front();
    }

    void pop() { // delete the first element
        q.erase(q.begin());
    }

    void clearQ() { // clean up
        q.clear();
    }

}; // end Queue

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
        bool operator==(const Process &p) const { return (OID == p.OID && Arrival == p.Arrival); }
        bool operator>(const Process &p) const {
            if (Arrival == p.Arrival) {
                return OID > p.OID;
            }
            return Arrival > p.Arrival;
        }
    };
    struct Process_State {
        int OID, Finish, Delay;
        Process_State() : OID(0), Finish(0), Delay(0) {}
        Process_State(int o, int f, int d) : OID(o), Finish(f), Delay(d) {}
    };

   public:
    static void shellsort(vector<Process> &p) {
        int n = p.size();
        for (int gap = n >> 1; gap > 0; gap >>= 1) {
            for (int i = gap; i < n; i++) {
                Process temp = p[i];
                int j;
                for (j = i; j >= gap; j -= gap) {
                    if (p[j - gap] > temp) {
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
    double avg_delay;
    double success_rate;

   public:
    void GetFile(ifstream &fp, ofstream &fout, string &filename, int caseNum) {
        do {
            cout << "\nInput a file name or number(type * to Go back): ";
            cin >> filename;
            if (filename == "*") {
                return;
            }
            if (filename.size() == 3) {
                if (caseNum == 1)
                    filename = "input" + filename + ".txt";
                else
                    filename = "sorted" + filename + ".txt";
            }
            fp.open(filename.c_str());
            if (!fp.is_open()) {
                cout << "\n### " << filename << " does not exist! ###" << endl;
            }
        } while (!fp.is_open());
        if (caseNum == 1)
            fout.open("sorted" + filename.substr(5, 3) + ".txt");
        else
            fout.open("output" + filename.substr(6, 3) + ".txt");
        return;
    }
    void Case1() {
        string filename;
        ifstream fp;
        ofstream fout;
        GetFile(fp, fout, filename, 1);
        if (filename == "*") {
            return;
        }

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

        cout << "\n\tOID\tArrival\tDuration\tTimeOut" << endl;
        for (int i = 0; i < n; ++i) {
            cout << "(" << i + 1 << ")"
                 << "\t" << ProcessList[i].OID << "\t" << ProcessList[i].Arrival << "\t"
                 << ProcessList[i].Duration << "\t" << ProcessList[i].Timeout << endl;
        }

        start = chrono::steady_clock::now();
        Data::shellsort(ProcessList);
        end = chrono::steady_clock::now();
        Sort_Time = chrono::duration_cast<chrono::microseconds>(end - start).count();
        start = chrono::steady_clock::now();
        fout << "OID\tArrival\tDuration\tTimeOut" << endl;
        for (int i = 0; i < n; ++i) {
            fout << ProcessList[i].OID << '\t' << ProcessList[i].Arrival << '\t' << ProcessList[i].Duration
                 << '\t' << ProcessList[i].Timeout << endl;
        }
        end = chrono::steady_clock::now();
        Write_Time = chrono::duration_cast<chrono::microseconds>(end - start).count();

        cout << "\nReading data: " << Read_Time << " us." << endl;
        cout << "Sorting data: " << Sort_Time << " us." << endl;
        cout << "Writing data: " << Write_Time << " us." << endl;

        cout << "\nSee sorted" << filename.substr(5, 3) << ".txt" << endl;
        fp.close();
        fout.close();
    }

    void ProcessOrder(int &now, Process o) {
        if (now > o.Timeout) {
            // cout << "Order " << o.OID << " is cancelled, now=" << now << endl;
            Fail.push_back(Process_State(o.OID, now, now - o.Arrival));
            return;
        }
        int finish = now + o.Duration;
        if (finish > o.Timeout) {
            // cancel
            now = o.Timeout;
            // cout << "Timeout when processing, Order " << o.OID << " is cancelled, now=" << now << endl;
            Fail.push_back(Process_State(o.OID, o.Timeout, o.Timeout - o.Arrival));
        } else {
            // process

            Success.push_back(Process_State(o.OID, finish, now - o.Arrival));
            now = finish;
            // cout << "Order " << o.OID << " is processed, now=" << now << endl;
            //  success
        }
    }
    void ProcessQueue(int &now, Queue<Process> &orders) {
        while (!orders.isEmpty()) {
            Process o;
            orders.getFront(o);
            orders.pop();
            ProcessOrder(now, o);
        }
    }
    void WriteOutput(ofstream &fout) {
        fout << "\t[Abort Jobs]" << endl;
        fout << "\tOID\tAbort\tDelay" << endl;
        int i = 1;
        avg_delay = 0;
        for (auto o : Fail) {
            fout << "[" << i << "]\t" << o.OID << "\t" << o.Finish << "\t" << o.Delay << endl;
            avg_delay += o.Delay;
            i++;
        }

        fout << "\t[Jobs Done]" << endl;
        fout << "\tOID\tDeparture\tDelay" << endl;
        i = 1;
        for (auto o : Success) {
            fout << "[" << i << "]\t" << o.OID << "\t" << o.Finish << "\t" << o.Delay << endl;
            avg_delay += o.Delay;
            i++;
        }
        avg_delay /= (Success.size() + Fail.size());
        success_rate = (double)Success.size() / (Success.size() + Fail.size()) * 100;
        fout.setf(ios::fixed);
        fout.precision(2);
        fout << "[Average Delay]\t" << avg_delay << " ms" << endl;
        fout << "[Success Rate]\t" << success_rate << " %" << endl;
    }
    void Case2() {
        string filename;
        ifstream fp;
        ofstream fout;
        GetFile(fp, fout, filename, 2);
        if (filename == "*") {
            return;
        }

        cout << "\nThe simulation is running..." << endl;

        string sch;
        for (int i = 0; i < 4; ++i) {
            fp >> sch; // read the first row
        }
        Queue<Process> orders;
        int now = 0;
        while (fp >> sch) {
            Process o;
            o.OID = stoi(sch);
            fp >> o.Arrival >> o.Duration >> o.Timeout;
            if (now < o.Arrival && orders.isEmpty()) { // idle
                now = o.Arrival;
            }
            if (now > o.Arrival) {
                if (!orders.isFull()) {
                    orders.push(o);
                    // cout << "CPU busy, Order " << o.OID << " is enqueued, now=" << now << endl;
                } else {
                    // cout << "Queue full, Order " << o.OID << " is rejected, now=" << now << endl;
                    Process_State ps(o.OID, o.Arrival, 0);
                    Fail.push_back(ps);
                    // cancel
                }

                continue;
            }
            int finish = now + o.Duration;
            if (finish > o.Timeout) {
                // cancel

                now = o.Timeout;
                // cout << "Timeout when processing, Order " << o.OID << " is cancelled, now=" << now << endl;
                Process_State ps(o.OID, o.Timeout, o.Timeout - o.Arrival);
                Fail.push_back(ps);
            } else {
                // process
                if (!orders.isEmpty()) { // CPU busy
                    ProcessQueue(now, orders);

                    if (now <= o.Arrival) {
                        now = o.Arrival;
                        int finish = now + o.Duration;
                        if (finish > o.Timeout) {
                            // cancel

                            now = o.Timeout;
                            // cout << "Timeout when processing, Order " << o.OID << " is cancelled, now=" <<
                            // now
                            //      << endl;
                            Fail.push_back(Process_State(o.OID, o.Timeout, o.Timeout - o.Arrival));
                        } else {
                            // process

                            Success.push_back(Process_State(o.OID, finish, now - o.Arrival));
                            now = finish;
                            // cout << "Order " << o.OID << " is processed, now=" << finish << endl;
                            //  success
                        }
                    } else {
                        orders.push(o);
                        // cout << "CPU busy, Order " << o.OID << " is enqueued, now=" << now << endl;
                    }
                } else {
                    // CPU idle, deal process immediately
                    Success.push_back(Process_State(o.OID, finish, now - o.Arrival));
                    now = finish;
                    // cout << "CPU idle, Order " << o.OID << " is processed, now=" << now << endl;
                }
            }
        }

        ProcessQueue(now, orders);

#ifdef DEBUG
        cout << "\033[1;32m"
             << "Success: \n";
        for (auto o : Success) {
            cout << o.OID << ' ' << o.Finish << ' ' << o.Delay << endl;
        }
        cout << "\033[0m" << endl;

        cout << "\033[1;31m"
             << "Fail: \n";
        for (auto o : Fail) {
            cout << o.OID << ' ' << o.Finish << ' ' << o.Delay << endl;
        }
        cout << "\033[0m" << endl;
#endif

        WriteOutput(fout);
        cout << "See output" << filename.substr(6, 3) << ".txt" << endl;
        fp.close();
    }
    void clear() {
        ProcessList.clear();
        Success.clear();
        Fail.clear();
    }
};
void WriteMenu() {
    cout << "\n**** Simulate FIFO Queues by SQF *****\n"
            "* 0. Quit                            *\n"
            "* 1. Sort a file                     *\n"
            "* 2. Simulate one FIFO queue         *\n"
            "**************************************\n";
    cout << "Input a command(0, 1, 2): ";
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
        } else if (command == "2") {
            s.Case2();
        } else
            cout << "\nCommand does not Exist!!!" << endl;
        WriteMenu();
        s.clear();
    }
    // cerr << "Time: " << (double)clock() / (double)CLOCKS_PER_SEC << '\n';
    return 0;
}
