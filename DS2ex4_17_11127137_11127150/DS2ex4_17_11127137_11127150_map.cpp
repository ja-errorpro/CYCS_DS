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
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// #include <bits/stdc++.h>
using namespace std;

#define endl '\n'
#define OFFSET 1e-6

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
    Node(string ID) : ID(ID), Nodesize(0) {}

    void addEdge(Node *dest, float weight) {
        adj.push_back({dest, weight});
        Nodesize++;
    }

    void sortAdj() {
        // sort(adj.begin(), adj.end(), [](const Edge &i, const Edge &j) { return i.first->ID < j.first->ID;
        // });
        stable_sort(adj.begin(), adj.end(),
                    [](const Edge &i, const Edge &j) { return i.first->ID < j.first->ID; });
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
        bool operator()(const pair<string, list<string>> &i, const pair<string, list<string>> &j) {
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

    unordered_map<string, unordered_set<string>> result_map; // for memory optimization
    set<string, less<string>> SingleSourceBFS2(Node *src) {
        // priority_queue<string, vector<string>, greater<string>> result;
        set<string, less<string>> result_set;

        unordered_set<string> visited;
        deque<string> bfs_queue;
        bfs_queue.push_back(src->ID);
        visited.insert(src->ID);
        while (!bfs_queue.empty()) {
            string current = bfs_queue.front();
            bfs_queue.pop_front();

            if (result_map[src->ID].count(current) == 0) {
                for (auto &i : result_map[current]) { // add previous result
                    visited.insert(i);
                    result_set.insert(i);
                    result_map[src->ID].insert(i);
                }
                for (auto &i : result_map[current]) { // search unvisited nodes
                    for (auto &j : edge_list[i]->adj) {
                        if (result_map[i].count(j.first->ID) == 0) continue;
                        // cerr << "current: " << current << " i: " << i << " j: " << j.first->ID << endl;
                        result_map[i].insert(j.first->ID);
                        if (visited.count(j.first->ID) == 0) {
                            bfs_queue.push_back(i);
                            break;
                        }
                    }
                }
            }
            for (auto &i : edge_list[current]->adj) {
                if (visited.count(i.first->ID) == 0) {
                    for (auto &j : result_map[i.first->ID]) {
                        result_map[current].insert(j);
                        result_map[src->ID].insert(j);
                        visited.insert(j);
                        result_set.insert(j);
                    }
                    if (result_map[i.first->ID].empty()) bfs_queue.push_back(i.first->ID);
                    visited.insert(i.first->ID);
                    result_map[current].insert(i.first->ID);
                    result_map[src->ID].insert(i.first->ID);
                    result_set.insert(i.first->ID);
                }
            }
        }

        result_set.erase(src->ID);

        return result_set;
    }

    set<string, less<string>> SingleSourceDFS(Node *src, float threshold) {
        // priority_queue<string, vector<string>, greater<string>> result;
        set<string, less<string>> result_set;

        unordered_set<string> visited;
        stack<string> dfs_stack;
        dfs_stack.push(src->ID);
        visited.insert(src->ID);
        while (!dfs_stack.empty()) {
            string current = dfs_stack.top();
            dfs_stack.pop();

            if (result_map[src->ID].count(current) == 0) {
                for (auto &i : result_map[current]) { // add previous result
                    visited.insert(i);
                    result_set.insert(i);
                    result_map[src->ID].insert(i);
                }
                for (auto &i : result_map[current]) { // search unvisited nodes
                    for (auto &j : edge_list[i]->adj) {
                        if (result_map[i].count(j.first->ID) == 0) continue;
                        // cerr << "current: " << current << " i: " << i << " j: " << j.first->ID << endl;
                        result_map[i].insert(j.first->ID);
                        if (visited.count(j.first->ID) == 0 && j.second >= threshold) {
                            dfs_stack.push(i);
                            break;
                        }
                    }
                }
            }
            for (auto &i : edge_list[current]->adj) {
                if (visited.count(i.first->ID) == 0 && i.second >= threshold) {
                    for (auto &j : result_map[i.first->ID]) {
                        result_map[current].insert(j);
                        result_map[src->ID].insert(j);
                        visited.insert(j);
                        result_set.insert(j);
                    }
                    if (result_map[i.first->ID].empty()) dfs_stack.push(i.first->ID);
                    visited.insert(i.first->ID);
                    result_map[current].insert(i.first->ID);
                    result_map[src->ID].insert(i.first->ID);
                    result_set.insert(i.first->ID);
                }
            }
        }

        result_set.erase(src->ID);

        return result_set;
    }

    void writeTraverseAll(string filename) {
        result_map.clear();
        ofstream fout(filename);
        fout << "<<< There are " << IDsize << " IDs in total. >>>" << endl;
        priority_queue<pair<string, list<string>>, vector<pair<string, list<string>>>, EdgeComparator>
            result_heap;
        for (auto &i : edge_list) result_map[i.first] = {};
        auto start = chrono::high_resolution_clock::now();
        for (auto &i : edge_list) {
            auto bfs_result = SingleSourceBFS2(i.second);
            list<string> tmp(bfs_result.begin(), bfs_result.end());
            result_heap.push({i.first, tmp});
        }
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        cerr << "Traverse Time: " << chrono::duration_cast<chrono::milliseconds>(elapsed).count() << " ms\n";
        int k = 1;
        while (!result_heap.empty()) {
            auto i = result_heap.top();
            result_heap.pop();
            fout << "[" << setw(3) << k++ << "] " << i.first << "(" << i.second.size() << "): \n";
            /*for (int j = 0; j < i.second.size(); j++) {
                fout << "\t(" << setw(2) << j + 1 << ") " << i.second.front();
                if ((j + 1) % 12 == 0) fout << endl;
            }*/
            int j = 0;
            for (auto &l : i.second) {
                fout << "\t(" << setw(2) << j + 1 << ") " << l;
                if ((j + 1) % 12 == 0) fout << endl;
                j++;
            }
            fout << endl;
        }
    }

    void writeTraverseWithThreshold(string filename, float threshold) {
        result_map.clear();
        ofstream fout(filename);

        priority_queue<pair<string, list<string>>, vector<pair<string, list<string>>>, EdgeComparator>
            result_heap;
        for (auto &i : edge_list) result_map[i.first] = {};
        for (auto &i : edge_list) {
            auto dfs_result = SingleSourceDFS(i.second, threshold);
            if (dfs_result.empty()) continue;
            list<string> tmp(dfs_result.begin(), dfs_result.end());
            result_heap.push({i.first, tmp});
        }
        cout << "\n<<< There are " << result_heap.size() << " IDs in total. >>>" << endl;
        fout << "<<< There are " << result_heap.size() << " IDs in total. >>>" << endl;
        int k = 1;
        while (!result_heap.empty()) {
            auto i = result_heap.top();
            result_heap.pop();
            fout << "[" << setw(3) << k++ << "] " << i.first << "(" << i.second.size() << "): \n";
            /*for (int j = 0; j < i.second.size(); j++) {
                fout << "\t(" << setw(2) << j + 1 << ") " << i.second.front();
                if ((j + 1) % 12 == 0) fout << endl;
            }*/
            int j = 0;
            for (auto &l : i.second) {
                fout << "\t(" << setw(2) << j + 1 << ") " << l;
                if ((j + 1) % 12 == 0) fout << endl;
                j++;
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
        cerr << "Traverse + Write File Time: " << chrono::duration_cast<chrono::milliseconds>(elapsed).count()
             << " ms\n";
    }

    void TraverseWithThreshold() {
        string output_file_name = "pairs" + file_number + ".inf";
        float threshold;
        cout << "\nInput a real number in [0.5,1]: ";
        cin >> threshold;
        while (threshold - 0.5 + OFFSET < 0 || threshold - 1 > OFFSET) {
            cout << "\n### It is NOT in [0.5,1] ###\n";
            cout << "\nInput a real number in [0.5,1]: ";
            cin >> threshold;
        }
        auto start = chrono::high_resolution_clock::now();
        graph.writeTraverseWithThreshold(output_file_name, threshold);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        // cerr << "Traverse + Write File Time: " <<
        // chrono::duration_cast<chrono::milliseconds>(elapsed).count()
        //      << " ms\n";
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
    void case3() {
        if (fileHandler.isEmpty()) {
            cout << "\n### There is no graph and choose 1 first. ###" << endl;
            return;
        }
        fileHandler.TraverseWithThreshold();
    }
};
void WriteMenu() {
    cout << "\n**** Graph data manipulation *****"
            "\n* 0. QUIT                        *"
            "\n* 1. Build adjacency lists       *"
            "\n* 2. Compute connection counts   *"
            "\n* 3. Estimate influence values   *"
            "\n* 4. Probability-based influence *"
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
        } else if (command == "3") {
            sol.case3();
        } else
            cout << "\nCommand does not Exist!!!" << endl;
        WriteMenu();
    }
    // cerr << "Time: " << (double)clock() / (double)CLOCKS_PER_SEC << '\n';
    return 0;
}
