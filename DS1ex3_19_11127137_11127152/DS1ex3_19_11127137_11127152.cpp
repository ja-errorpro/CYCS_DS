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
    struct Node { // circular doubly linked lists
        T data;
        Node *next;
        Node *prev;
        Node(const T &d) : data(d), next(nullptr), prev(nullptr) {}
    };
    Node *head;
    Node *tail;
    int size;

   public:
    Queue() : head(nullptr), tail(nullptr), size(0) {}
    void PrintAll() {
        Node *temp = head;
        for (int i = 0; i < size; ++i) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
    int length() const { // get the current queue length
        return size;
    }

    bool isEmpty() const { // check whether it is empty
        return size == 0;
    }

    bool isFull() const { // check whether it is full
        return length() >= queueMax;
    }

    void push(const T &input) { // add the new element at last
        Node **h = &head;
        Node **t = &tail;
        Node *newNode = new Node(input);
        if (isEmpty()) {
            *h = newNode;
            *t = newNode;
            newNode->next = newNode;
            newNode->prev = newNode;
        } else {
            (*t)->next = newNode;
            newNode->prev = *t;
            newNode->next = *h;
            (*h)->prev = newNode;
            *t = newNode;
        }
        size++;
    }

    void getFront(T &first) { // get the first element
        if (head == nullptr) {
            cerr << "\033[1;31mQueue is empty!\033[0m" << endl;
        }
        first = head->data;
    }

    void pop() { // delete the first element
        Node **h = &head;
        Node **t = &tail;
        if (isEmpty()) {
            cerr << "\033[1;31mQueue is empty!\033[0m" << endl;
        } else if (length() == 1) {
            delete *h;
            *h = nullptr;
            *t = nullptr;
        } else {
            Node *temp = *h;
            *h = (*h)->next;
            (*h)->prev = *t;
            (*t)->next = *h;
            delete temp;
        }
        size--;
    }

    void clear() { // clean up
        while (!isEmpty()) {
            pop();
        }
    }
    ~Queue() { // destructor
        clear();
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
        friend ostream &operator<<(ostream &os, const Process &p) {
            os << p.OID;
            return os;
        }
    };
    struct Process_State {
        int OID, CID, Finish, Delay;
        Process_State() : OID(0), CID(0), Finish(0), Delay(0) {}
        Process_State(int o, int f, int d) : OID(o), Finish(f), Delay(d), CID(1) {}
        Process_State(int o, int c, int f, int d) : OID(o), Finish(f), Delay(d), CID(c) {}
    };

   public:
    static void shellsort(vector<Process> &p) {
        int n = p.size();
        for (uint32_t gap = n >> 1; gap > 0; gap >>= 1) {
            for (int i = gap; i < n; i++) {
                Process temp = p[i];
                uint32_t j;
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
    /*
      load a file from user's input
    @param fp: the file stream
    @param fout: the output file stream
    @param filename: the file name
    @param caseNum: 1 for case 1, 2 for case 2
    @side effect: initialize the file stream
    */
    void GetFile(ifstream &fp, ofstream &fout, string &filename, int caseNum) {
        // do {
        string output_filename;
        string input_filename;
        cout << "\nInput a file number: ";
        cin >> filename;
        /*
        if (filename == "*") {
            return;
        }
        if (filename.size() == 3) {
            if (caseNum == 1)
                filename = "input" + filename + ".txt";
            else
                filename = "sorted" + filename + ".txt";
        }*/
        if (caseNum == 1) {
            input_filename = "input" + filename + ".txt";
            output_filename = "sorted" + filename + ".txt";
        } else if (caseNum == 2) {
            input_filename = "sorted" + filename + ".txt";
            output_filename = "output" + filename + ".txt";
        } else {
            input_filename = "sorted" + filename + ".txt";

            output_filename = "double" + filename + ".txt";
        }
        fp.open(input_filename.c_str());
        if (!fp.is_open()) {
            cout << "\n### " << input_filename << " does not exist! ###" << endl;
            filename = "*";
            return;
        }
        //} while (!fp.is_open());
        fout.open(output_filename);
        filename = output_filename;
        return;
    }
    /*
        load a file from user's input
    @param fp: the file stream
    @param filename: the file name
    @param caseNum: 1 for case 1, 2 for case 2
    @side effect: initialize the file stream
    */
    void GetFile(ifstream &fp, string &filename, int caseNum) {
        // do {
        string input_filename;
        cout << "\nInput a file number: ";
        cin >> filename;
        /*if (filename == "*") {
            return;
        }
        if (filename.size() == 3) {
            if (caseNum == 1)
                filename = "input" + filename + ".txt";
            else
                filename = "sorted" + filename + ".txt";
        }*/
        if (caseNum == 1) {
            input_filename = "input" + filename + ".txt";
        } else {
            input_filename = "sorted" + filename + ".txt";
        }
        fp.open(input_filename.c_str());
        if (!fp.is_open()) {
            cout << "\n### " << input_filename << " does not exist! ###" << endl;
            filename = "*";
            return;
        }
        //} while (!fp.is_open());
        filename = input_filename;
        return;
    }
    /*
        load process list from file
    @param fp: the file stream
    @return: the process list
    */
    vector<Process> getProcessList(ifstream &fp) {
        vector<Process> ProcessList;
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
        Read_Time = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        return ProcessList;
    }
    /*
        output process list
    */
    void WriteProcessList() {
        cout << "\n\tOID\tArrival\tDuration\tTimeOut" << endl;
        int n = ProcessList.size();
        for (int i = 0; i < n; ++i) {
            cout << "(" << i + 1 << ")"
                 << "\t" << ProcessList[i].OID << "\t" << ProcessList[i].Arrival << "\t"
                 << ProcessList[i].Duration << "\t" << ProcessList[i].Timeout << endl;
        }
    }
    /*
        output process list to ofstream
        @param fout: the output file stream
    */
    void WriteProcessList(ofstream &fout) {
        chrono::steady_clock::time_point start = chrono::steady_clock::now();
        fout << "OID\tArrival\tDuration\tTimeOut" << endl;
        int n = ProcessList.size();
        for (int i = 0; i < n; ++i) {
            fout << ProcessList[i].OID << '\t' << ProcessList[i].Arrival << '\t' << ProcessList[i].Duration
                 << '\t' << ProcessList[i].Timeout << endl;
        }
        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        Write_Time = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    }
    /*
        sort process list
    */
    void Case1() {
        string filename;
        ifstream fp;
        ofstream fout;
        GetFile(fp, fout, filename, 1);
        if (filename == "*") {
            return;
        }

        ProcessList = getProcessList(fp);
        WriteProcessList();

        chrono::steady_clock::time_point start = chrono::steady_clock::now();
        Data::shellsort(ProcessList);
        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        Sort_Time = chrono::duration_cast<chrono::milliseconds>(end - start).count();

        WriteProcessList(fout);

        cout << "\nReading data: " << Read_Time << " ms." << endl;
        cout << "Sorting data: " << Sort_Time << " ms." << endl;
        cout << "Writing data: " << Write_Time << " ms." << endl;

        cout << "\nSee " << filename << endl;
        fp.close();
        fout.close();
    }
    /*
        process an order
        @param now: the current time
        @param o: the order
        @side effect: update the now, and push the result to Success or Fail list
    */
    void ProcessOrder(int &now, Process o) {
        if (now < o.Arrival) now = o.Arrival;
        if (now > o.Timeout) {
            // cout << "\033[1;31mOrder " << o.OID << " is cancelled, now=" << now << "\033[0m" << endl;
            Fail.push_back(Process_State(o.OID, now, now - o.Arrival));
            return;
        }
        int finish = now + o.Duration;
        if (finish > o.Timeout) {
            // cancel
            now = o.Timeout;
            // cout << "\033[1;31mTimeout when processing, Order " << o.OID << " is cancelled, now=" << now
            //      << "\033[0m" << endl;
            Fail.push_back(Process_State(o.OID, o.Timeout, o.Timeout - o.Arrival));
        } else {
            // process

            Success.push_back(Process_State(o.OID, finish, now - o.Arrival));
            now = finish;
            // cout << "\033[1;32mOrder " << o.OID << " in Queue is processed, now=" << finish << "\033[0m"
            //     << endl;
            //  success
        }
    }
    void ProcessOrder(int &now, Process o, int CPUid) {
        // if (now < o.Arrival) now = o.Arrival;
        if (now > o.Timeout) {
            // cout << "\033[1;31mOrder " << o.OID << " is cancelled, now=" << now << "\033[0m" << endl;

            Fail.push_back(Process_State(o.OID, CPUid, now, now - o.Arrival));
            return;
        }
        int finish = now + o.Duration;
        if (finish > o.Timeout) {
            // cancel
            now = o.Timeout;

            // cout << "\033[1;31mTimeout when processing, Order " << o.OID << " is cancelled,
            // now=" << now
            //      << "\033[0m" << endl;

            Fail.push_back(Process_State(o.OID, CPUid, o.Timeout, o.Timeout - o.Arrival));
        } else {
            // process

            Success.push_back(Process_State(o.OID, CPUid, finish, now - o.Arrival));
            now = finish;

            // cout << "\033[1;32mOrder " << o.OID << " in Queue " << CPUid << " is processed, now=" << finish
            //      << "\033[0m" << endl;

            //  success
        }
    }
    /*
        process the orders in queue
        @param now: the current time
        @param orders: the queue
        @side effect: update the now, and push the result to Success or Fail list
    */
    void ProcessQueue(int &now, Queue<Process> &orders) {
        if (!orders.isEmpty()) {
            Process o;
            orders.getFront(o);
            orders.pop();
            ProcessOrder(now, o);
        }
    }
    void ProcessQueue(int &now, Queue<Process> &orders, int CPUid) {
        if (!orders.isEmpty()) {
            Process o;
            orders.getFront(o);
            orders.pop();
            ProcessOrder(now, o, CPUid);
        }
    }
    /*
        output the result
    */
    void WriteResult() {
        cout << "\t[Abort Jobs]" << endl;
        cout << "\tOID\tAbort\tDelay" << endl;
        int i = 1;
        avg_delay = 0;
        for (auto o : Fail) {
            cout << "[" << i << "]\t" << o.OID << "\t" << o.Finish << "\t" << o.Delay << endl;
            avg_delay += o.Delay;
            i++;
        }

        cout << "\t[Jobs Done]" << endl;
        cout << "\tOID\tDeparture\tDelay" << endl;
        i = 1;
        for (auto o : Success) {
            cout << "[" << i << "]\t" << o.OID << "\t" << o.Finish << "\t" << o.Delay << endl;
            avg_delay += o.Delay;
            i++;
        }
        if (Success.size() + Fail.size() == 0) {
            avg_delay = 0;
            success_rate = 0;
        } else {
            avg_delay /= (Success.size() + Fail.size());
            success_rate = (double)Success.size() / (Success.size() + Fail.size()) * 100;
        }
        cout.setf(ios::fixed);
        cout.precision(2);
        cout << "[Average Delay]\t" << avg_delay << " ms" << endl;
        cout << "[Success Rate]\t" << success_rate << " %" << endl;
    }
    /*
        output the result to ofstream
        @param fout: the output file stream
    */
    void WriteResult(ofstream &fout) {
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
        if (Success.size() + Fail.size() == 0) {
            avg_delay = 0;
            success_rate = 0;
        } else {
            avg_delay /= (Success.size() + Fail.size());
            success_rate = (double)Success.size() / (Success.size() + Fail.size()) * 100;
        }
        fout.setf(ios::fixed);
        fout.precision(2);
        fout << "[Average Delay]\t" << avg_delay << " ms" << endl;
        fout << "[Success Rate]\t" << success_rate << " %" << endl;
    }
    /*
        output the result to ofstream with CPU id
        @param fout: the output file stream
    */
    void WriteResultCID(ofstream &fout) {
        fout << "\t[Abort Jobs]" << endl;
        fout << "\tOID\tCID\tAbort\tDelay" << endl;
        int i = 1;
        avg_delay = 0;
        for (auto o : Fail) {
            fout << "[" << i << "]\t" << o.OID << "\t" << o.CID << "\t" << o.Finish << "\t" << o.Delay
                 << endl;
            avg_delay += o.Delay;
            i++;
        }

        fout << "\t[Jobs Done]" << endl;
        fout << "\tOID\tCID\tDeparture\tDelay" << endl;
        i = 1;
        for (auto o : Success) {
            fout << "[" << i << "]\t" << o.OID << "\t" << o.CID << "\t" << o.Finish << "\t" << o.Delay
                 << endl;
            avg_delay += o.Delay;
            i++;
        }
        if (Success.size() + Fail.size() == 0) {
            avg_delay = 0;
            success_rate = 0;
        } else {
            avg_delay /= (Success.size() + Fail.size());
            success_rate = (double)Success.size() / (Success.size() + Fail.size()) * 100;
        }
        fout.setf(ios::fixed);
        fout.precision(2);
        fout << "[Average Delay]\t" << avg_delay << " ms" << endl;
        fout << "[Success Rate]\t" << success_rate << " %" << endl;
    }
    /*
        simulataion of process orders
    */
    void Simulate() {
        Queue<Process> orders;
        int now = 0;
        for (auto o : ProcessList) {
            if (o.Arrival > o.Timeout) { // ??? illegal order
                continue;
            }
            if (now < o.Arrival && orders.isEmpty()) { // idle
                now = o.Arrival;
            }

            if (now > o.Arrival) {
                if (!orders.isFull()) {
                    orders.push(o);
                    // cout << "\033[1;33mOrder " << o.OID
                    //      << " has arrived before, so it is enqueued, now=" << now << "\033[0m" << endl;
                } else {
                    // cout << "\033[1;31mQueue is full, Order " << o.OID << " is rejected, now=" << now
                    //      << "\033[0m" << endl;
                    Fail.push_back(Process_State(o.OID, o.Arrival, 0));
                    // cancel
                }

                continue;
            }

            // process
            if (!orders.isEmpty()) { // CPU busy
                // cout << "\033[1;35m<!>\033[0m CPU idle, but queue is not empty, process queue first"
                //      << endl;
                ProcessQueue(now, orders);
                orders.push(o);
            } else {
                int finish = now + o.Duration;
                if (finish > o.Timeout) {
                    // cancel

                    now = o.Timeout;
                    // cout << "\033[1;31mTimeout when processing, Order " << o.OID << " is cancelled, now="
                    // << now
                    //      << "\033[0m" << endl;
                    Fail.push_back(Process_State(o.OID, o.Timeout, o.Timeout - o.Arrival));
                } else {
                    // CPU idle, deal process immediately
                    Success.push_back(Process_State(o.OID, finish, now - o.Arrival));
                    now = finish;
                    // cout << "\033[1;32mCPU idle, Order " << o.OID << " is processed, now=" << now <<
                    // "\033[0m"
                    //      << endl;
                }
            }
        }
        while (!orders.isEmpty()) ProcessQueue(now, orders);
    }
    void Simulate(vector<Queue<Process>> &CPU_Queue_arr) {
        vector<int> cpu_curtime_arr(2, 0);
        int cpu_num = CPU_Queue_arr.size();
        for (auto o : ProcessList) {
            /*
            cout << "\033[1;34mOrder " << o.OID << " has arrived"
                 << ", cpu1=" << cpu_curtime_arr[0] << ", cpu2=" << cpu_curtime_arr[1] << "\033[0m" << endl;
            cout << "Queue 1:";
            CPU_Queue_arr[0].PrintAll();
            cout << "Queue 2:";
            CPU_Queue_arr[1].PrintAll();

*/

            if (!CPU_Queue_arr[0].isEmpty()) {
                // cout << "\033[1;35m<!>\033[0m CPU " << idle_cpu + 1 << " is idle, process queue " << endl;
                while (!CPU_Queue_arr[0].isEmpty() && cpu_curtime_arr[0] <= o.Arrival)
                    ProcessQueue(cpu_curtime_arr[0], CPU_Queue_arr[0], 1);
            }
            if (!CPU_Queue_arr[1].isEmpty()) {
                // cout << "\033[1;35m<!>\033[0m CPU " << idle_cpu + 1 << " is idle, process queue " << endl;
                while (!CPU_Queue_arr[1].isEmpty() && cpu_curtime_arr[1] <= o.Arrival)
                    ProcessQueue(cpu_curtime_arr[1], CPU_Queue_arr[1], 2);
            }

            // choose which cpu is idle
            int idle_cpu = -1;
            for (int i = 0; i < cpu_num; ++i) {
                if (cpu_curtime_arr[i] <= o.Arrival) {
                    idle_cpu = i;
                    // cpu_curtime_arr[i] = o.Arrival;
                    break;
                }
            }

            // if there is an idle cpu, process the order
            if (idle_cpu != -1) {
                /*cout << "\033[1;35m<!>\033[0m CPU " << idle_cpu + 1 << " is idle, process order " << o.OID
                     << endl;*/

                if (cpu_curtime_arr[idle_cpu] < o.Arrival) {
                    cpu_curtime_arr[idle_cpu] = o.Arrival;
                    /*cout << "\033[1;35m<!>\033[0m CPU " << idle_cpu + 1 << " is idle, process order " <<
                       o.OID
                         << endl;*/
                    ProcessOrder(cpu_curtime_arr[idle_cpu], o, idle_cpu + 1);
                } else {
                    /*cout << "\033[1;35m<!>\033[0m CPU " << idle_cpu + 1 << " is idle, enqueue order " <<
                       o.OID
                         << endl;*/
                    CPU_Queue_arr[idle_cpu].push(o);
                }

                continue;
            }

            // if there is no idle cpu, choose the cpu with the shortest queue
            int shortest_queue = 0;
            for (int i = 1; i < cpu_num; ++i) {
                if (CPU_Queue_arr[i].length() < CPU_Queue_arr[shortest_queue].length()) {
                    shortest_queue = i;
                }
            }
            /*cout << "\033[1;35m<!>\033[0m CPU " << shortest_queue + 1 << " is chosen, enqueue order " <<
               o.OID
                 << endl;*/
            if (!CPU_Queue_arr[shortest_queue].isFull()) {
                CPU_Queue_arr[shortest_queue].push(o);
            } else {
                /*cout << "\033[1;31mQueue is full, Order " << o.OID
                     << " is rejected, now=" << cpu_curtime_arr[shortest_queue] << "\033[0m" << endl;*/
                Fail.push_back(Process_State(o.OID, 0, o.Arrival, 0));
            }
        }
        while (!CPU_Queue_arr[0].isEmpty()) ProcessQueue(cpu_curtime_arr[0], CPU_Queue_arr[0], 1);
        while (!CPU_Queue_arr[1].isEmpty()) ProcessQueue(cpu_curtime_arr[1], CPU_Queue_arr[1], 2);
    }
    /*
        simulataion of process orders and output the result
    */
    void Case2() {
        string filename;
        ifstream fp;
        ofstream fout;
        GetFile(fp, fout, filename, 2);
        if (filename == "*") {
            return;
        }

        cout << "\nThe simulation is running..." << endl;
        ProcessList = getProcessList(fp);
        Simulate();
        WriteResult(fout);
        cout << "See " << filename << endl;
        fp.close();
    }
    /*
        simulataion of process orders and output the result
    */
    void Case3() {
        string filename;
        ifstream fp;
        ofstream fout;
        GetFile(fp, fout, filename, 3);
        if (filename == "*") {
            return;
        }

        cout << "\nThe simulation is running..." << endl;
        ProcessList = getProcessList(fp);
        vector<Queue<Process>> CPU_Queue_arr(2, Queue<Process>());
        Simulate(CPU_Queue_arr);
        WriteResultCID(fout);
        cout << "See " << filename << endl;
        fp.close();
    }
    /*
        clear the lists
    */
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
            "* 3. Simulate two queues by SQF      *\n"
            "**************************************\n";
    cout << "Input a command(0, 1, 2, 3): ";
}
int main() {
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
        } else if (command == "3") {
            s.Case3();
        } else
            cout << "\nCommand does not Exist!!!" << endl;
        WriteMenu();
        s.clear();
    }
    return 0;
}
