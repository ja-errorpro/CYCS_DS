// 11127137, 黃乙家, 11127150, 張睿恩
/****************************************************/
/*  CPP Template for School                         */
/*  Author: CompileErr0r(YiJia)                     */
/*  Author ID: 11127137                             */
/*  Compile Environment: Linux 5.15.90.1 WSL x86_64 */
/*  Compiler: g++ 9.4                               */
/****************************************************/

#pragma GCC optimize("Ofast")
#pragma loop_opt(on)

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <new>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// #include <bits/stdc++.h>
using namespace std;

#define endl '\n'

#define CompileErr0r_is_the_weakest_hacker ios_base::sync_with_stdio(0);

template <typename... rest>
void VERBOSE(rest... args) {
#ifdef CompileErr0rDEBUGGING
    cout << "\033[1;37m[\033[1;33mDEBUG\033[1;37m]\033[0m ";
    initializer_list<int>{(cout << args, 0)...};
#endif
}

#define Edge pair<Node *, float>

struct StudentData {
    char postID[12];
    char getID[12];
    float weight;
    StudentData() : weight(0) {}
};

struct Node {
    string ID;
    vector<Edge> adj;
    int Nodesize;
    int depth;
    Node(string ID) : ID(ID), Nodesize(0), depth(0) {}

    void addEdge(Node *dest, float weight) {
        adj.push_back({dest, weight});
        Nodesize++;
    }

    void sortAdj() {
        sort(adj.begin(), adj.end(), [](const Edge &i, const Edge &j) { return i.first->ID < j.first->ID; });
    }
};

class adjList {
   private:
    int IDsize;
    int Nodesize;

   public:
    // vector<Node *> list;
    map<string, Node *, less<string>> edge_list;
    ~adjList() { clear(); }
    void build(vector<StudentData> data) {
        for (auto &i : data) {
            if (edge_list.count(i.postID) == 0) {
                edge_list[i.postID] = new Node(i.postID);
            }
            if (edge_list.count(i.getID) == 0) {
                edge_list[i.getID] = new Node(i.getID);
            }
            edge_list[i.postID]->addEdge(edge_list[i.getID], i.weight);
        }
        for (auto &i : edge_list) {
            i.second->sortAdj();
        }

        // sort(list.begin(), list.end(), [](const Node *i, const Node *j) { return i->ID < j->ID; });
        IDsize = edge_list.size();
    }

    void clear() {
        for (auto &i : edge_list) {
            delete i.second;
        }
        edge_list.clear();
        IDsize = 0;
        Nodesize = 0;
    }

    void printNodes() {
        Nodesize = 0;
        /*for (int i = 0; i < list.size(); i++) {
            cout << "\n[" << i + 1 << "] " << list[i]->ID << ": ";
            for (int j = 0; j < list[i]->adj.size(); j++) {
                cout << "(" << j + 1 << ") " << list[i]->adj[j].first->ID << ", " << list[i]->adj[j].second
                     << " ";
                Nodesize++;
            }
        }*/

        for (auto &i : edge_list) {
            cout << "\n[" << i.first << "] " << i.second->ID << ": ";
            for (int j = 0; j < i.second->adj.size(); j++) {
                cout << "(" << j + 1 << ") " << i.second->adj[j].first->ID << ", " << i.second->adj[j].second
                     << " ";
                Nodesize++;
            }
        }
    }

    void writeToFile(string filename) {
        Nodesize = 0;
        ofstream fout(filename);
        fout << "<<< There are " << IDsize << " IDs in total. >>>" << endl;
        /*for (int i = 0; i < list.size(); i++) {
            fout << "[" << setw(3) << i + 1 << "] " << list[i]->ID << ": \n";
            for (int j = 0; j < list[i]->adj.size(); j++) {
                fout << "\t(" << setw(2) << j + 1 << ") " << list[i]->adj[j].first->ID << ", " << setw(5)
                     << list[i]->adj[j].second;
                Nodesize++;
                if ((j + 1) % 12 == 0) fout << endl;
            }
            fout << endl;
        }*/
        int k = 1;
        for (auto &i : edge_list) {
            fout << "[" << setw(3) << k++ << "] " << i.second->ID << ": \n";
            for (int j = 0; j < i.second->adj.size(); j++) {
                fout << "\t(" << setw(2) << j + 1 << ") " << i.second->adj[j].first->ID << ", " << setw(6)
                     << i.second->adj[j].second;
                Nodesize++;
                if ((j + 1) % 12 == 0) fout << endl;
            }
            fout << endl;
        }

        fout << "<<< There are " << Nodesize << " nodes in total. >>>" << endl;
    }

    void printIDSize() { cout << "\n<<< There are " << IDsize << " IDs in total. >>>" << endl; }

    void printNodeSize() { cout << "\n<<< There are " << Nodesize << " nodes in total. >>>" << endl; }

    struct EdgeComparator {
        bool operator()(const Edge &i, const Edge &j) { return i.first->ID > j.first->ID; }
        bool operator()(const pair<string, vector<Edge>> &i, const pair<string, vector<Edge>> &j) {
            if (i.second.size() == j.second.size()) return i.first > j.first;
            return i.second.size() < j.second.size();
        }
        bool operator()(const pair<string, vector<string>> &i, const pair<string, vector<string>> &j) {
            if (i.second.size() == j.second.size()) return i.first > j.first;
            return i.second.size() < j.second.size();
        }
    };
    priority_queue<Edge, vector<Edge>, EdgeComparator> SingleSourceBFS(Node *src) {
        priority_queue<Edge, vector<Edge>, EdgeComparator> result;
        unordered_set<Node *> visited;

        queue<Node *> bfs_queue;
        bfs_queue.push(src);
        visited.insert(src);

        while (!bfs_queue.empty()) {
            Node *current = bfs_queue.front();
            bfs_queue.pop();
            for (auto &i : current->adj) {
                if (visited.count(i.first) == 0) {
                    bfs_queue.push(i.first);
                    visited.insert(i.first);
                    result.push(i);
                    // sort(result.begin(), result.end(),
                    //     [](const Edge &i, const Edge &j) { return i.first->ID < j.first->ID; });
                }
            }
        }
        return result;
    }

    struct CompareCost {
        bool operator()(const Node *a, const Node *b) { return a->depth < b->depth; }
        bool operator()(const priority_queue<string, vector<string>, greater<string>> &a,
                        const priority_queue<string, vector<string>, greater<string>> &b) {
            return a.size() < b.size();
        }
    };

    // use priority queue
    priority_queue<Edge, vector<Edge>, EdgeComparator> SingleSourceBFS2(Node *src) {
        priority_queue<Edge, vector<Edge>, EdgeComparator> result;
        unordered_map<string, bool> visited;

        priority_queue<Node *, vector<Node *>, CompareCost> bfs_first_queue;
        bfs_first_queue.push(src);
        visited[src->ID] = 1;

        while (!bfs_first_queue.empty()) {
            Node *current = bfs_first_queue.top();

            bfs_first_queue.pop();
            for (auto &i : current->adj) {
                if (visited.count(i.first->ID) == 0) {
                    bfs_first_queue.push(i.first);
                    i.first->depth = current->depth + 1;
                    visited[i.first->ID] = 1;
                    result.push(i);
                }
            }
        }

        return result;
    }

    void writeTraverseAll(string filename) {
        ofstream fout(filename);
        fout << "<<< There are " << IDsize << " IDs in total. >>>" << endl;
        priority_queue<pair<string, vector<Edge>>, vector<pair<string, vector<Edge>>>, EdgeComparator>
            result_heap;

        for (auto &i : edge_list) {
            auto bfs_result = SingleSourceBFS2(i.second);
            vector<Edge> tmp;
            while (!bfs_result.empty()) {
                tmp.push_back(bfs_result.top());
                bfs_result.pop();
            }
            result_heap.push({i.first, tmp});
        }

        int k = 1;
        while (!result_heap.empty()) {
            auto i = result_heap.top();
            result_heap.pop();
            fout << "[" << setw(3) << k++ << "] " << i.first << "(" << i.second.size() << "): \n";
            for (int j = 0; j < i.second.size(); j++) {
                fout << "\t(" << setw(2) << j + 1 << ") " << i.second[j].first->ID;
                if ((j + 1) % 12 == 0) fout << endl;
            }
            fout << endl;
        }
    }
};

class FileHandler {
   private:
    string input_file_name;
    string file_number;
    vector<StudentData> original_student_data;
    adjList graph;

   public:
    FileHandler() {}
    ~FileHandler() { clear(); }
    bool isEmpty() { return input_file_name.empty(); }
    void clear() {
        input_file_name.clear();
        file_number.clear();
        original_student_data.clear();
        graph.clear();
    }

    int read() {
        if (input_file_name.empty()) {
            cout << "\nInput a file number ([0] Quit): ";
            cin >> file_number;
            cin.ignore();
            if (file_number == "0") {
                file_number.clear();
                return -2;
            }
            input_file_name = "pairs" + file_number + ".bin";
        }
        ifstream fin(input_file_name);
        int transformed = 0;
        if (!fin.is_open()) {
            cout << "\n### " << input_file_name << " does not exist! ###" << endl;
            // transformed = transformTextToBin(file_number);
            transformed = -1;
        }
        if (transformed == -1) return transformed;
        fin.close();
        return 0;
    }

    void readData() {
        ifstream fin(input_file_name, ios::binary);
        StudentData tmp;
        while (fin.read((char *)&tmp, sizeof(StudentData))) {
            if (fin.bad()) {
                cerr << "### Bad bit. ###" << endl;
                break;
            } else if (fin.fail()) {
                cerr << "### Fail bit. ###" << endl;
                break;
            }
            original_student_data.push_back(tmp);
        }
        fin.close();
    }

    void buildGraph() { graph.build(original_student_data); }

    void writeGraph() {
        string output_file_name = "pairs" + file_number + ".adj";
        graph.writeToFile(output_file_name);
        graph.printIDSize();
        graph.printNodeSize();
    }

    void TraverseGraph() {
        string output_file_name = "pairs" + file_number + ".cnt";
        graph.printIDSize();
        auto start = chrono::high_resolution_clock::now();
        graph.writeTraverseAll(output_file_name);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        // cerr << "Time: " << chrono::duration_cast<chrono::milliseconds>(elapsed).count() << " ms\n";
    }
};

class Solution {
    FileHandler fileHandler;

   public:
    Solution() {}
    void case1() {
        fileHandler.clear();
        if (fileHandler.read() < 0) return;
        fileHandler.readData();
        fileHandler.buildGraph();
        fileHandler.writeGraph();
    }
    void case2() {
        if (fileHandler.isEmpty()) {
            cout << "\n### There is no graph and choose 1 first. ###" << endl;
            return;
        }
        fileHandler.TraverseGraph();
    }
};
void WriteMenu() {
    cout << "\n**** Graph data manipulation *****"
            "\n* 0. QUIT                        *"
            "\n* 1. Build adjacency lists       *"
            "\n* 2. Compute connection counts   *"
            "\n**********************************"
            "\nInput a choice(0, 1, 2): ";
}

signed main() {
    CompileErr0r_is_the_weakest_hacker;
    string command;
    Solution sol;
    // use string to avoid malicious input
    WriteMenu();
    while (cin >> command && command != "0") {
        cin.ignore();
        if (command == "1") {
            sol.case1();
        } else if (command == "2") {
            sol.case2();
        } else
            cout << "\nCommand does not Exist!!!" << endl;
        WriteMenu();
    }
    // cerr << "Time: " << (double)clock() / (double)CLOCKS_PER_SEC << '\n';
    return 0;
}
