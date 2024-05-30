// 11127137, 黃乙家
/****************************************************/
/*  CPP Template for School                         */
/*  Author: CompileErr0r(YiJia)                     */
/*  Author ID: 11127137                             */
/*  Compile Environment: Linux 5.15.90.1 WSL x86_64 */
/*  Compiler: g++ 9.4                               */
/****************************************************/

#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <new>
#include <set>
#include <string>
#include <vector>

#pragma GCC optimize("Ofast")
#pragma loop_opt(on)

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

const int MAX_BUFFER_SIZE = 300;

struct StudentData {
    char postID[10];
    char getID[10];
    float weight;
    StudentData() : weight(0) {}
};

class FileHandler {
   private:
    string input_file_name;
    string file_number;
    vector<StudentData> partial_student_data;

    int split_count;

   public:
    FileHandler() : split_count(0) {}
    ~FileHandler() { clear(); }
    void clear() {
        input_file_name.clear();
        file_number.clear();
        partial_student_data.clear();
    }

    bool empty() { return input_file_name.empty(); }

    int read() {
        if (input_file_name.empty()) {
            cout << "\nInput the file name: [0]Quit\n";
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
            cout << "\n" << input_file_name << " does not exist!!!" << endl;
            // transformed = transformTextToBin(file_number);
            transformed = -1;
        }
        if (transformed == -1) return transformed;
        fin.close();
        return 0;
    }

    void writePartialSortedData(int index) { // write partial sorted data to file
        string output_file_name = "tmp_" + to_string(index);
        ofstream fout(output_file_name, ios::binary);
        for (auto &student : partial_student_data) {
            fout.write((char *)&student, sizeof(StudentData));
        }
        fout.close();
    }

    void calculateSplitCount() {
        ifstream fin(input_file_name, ios::binary);
        fin.seekg(0, ios::end);
        int file_size = fin.tellg();
        fin.close();
        split_count = file_size / (MAX_BUFFER_SIZE * sizeof(StudentData));
        if (file_size % (MAX_BUFFER_SIZE * sizeof(StudentData)) != 0) split_count++;
    }

    void splitData() {
        ifstream fin(input_file_name, ios::binary);
        calculateSplitCount();
        for (int i = 0; i < split_count; i++) {
            partial_student_data.clear();
            for (int j = 0; j < MAX_BUFFER_SIZE; j++) {
                StudentData student;
                fin.read((char *)&student, sizeof(StudentData));
                if (fin.eof()) break;
                partial_student_data.push_back(student);
            }
            stable_sort(
                partial_student_data.begin(), partial_student_data.end(),
                [](const StudentData &a, const StudentData &b) { return a.weight - b.weight > 1e-6; });
            writePartialSortedData(i);
        }
        fin.close();
    }

    void twoWayMergeFile(string left_file, string right_file, string tmp_file) {
        ifstream left_fin("tmp_" + left_file, ios::binary);
        ifstream right_fin("tmp_" + right_file, ios::binary);
        ofstream fout("tmp_" + tmp_file, ios::binary);
        StudentData left_student, right_student;
        left_fin.read((char *)&left_student, sizeof(StudentData));
        right_fin.read((char *)&right_student, sizeof(StudentData));
        while (!left_fin.eof() && !right_fin.eof()) {
            if (left_student.weight >= right_student.weight) {
                fout.write((char *)&left_student, sizeof(StudentData));
                left_fin.read((char *)&left_student, sizeof(StudentData));
            } else {
                fout.write((char *)&right_student, sizeof(StudentData));
                right_fin.read((char *)&right_student, sizeof(StudentData));
            }
        }
        while (!left_fin.eof()) {
            fout.write((char *)&left_student, sizeof(StudentData));
            left_fin.read((char *)&left_student, sizeof(StudentData));
        }
        while (!right_fin.eof()) {
            fout.write((char *)&right_student, sizeof(StudentData));
            right_fin.read((char *)&right_student, sizeof(StudentData));
        }
        left_fin.close();
        right_fin.close();
        fout.close();
    }

    void mergeFile() {
        vector<string> file_name;
        set<string> all_file;
        for (int i = 0; i < split_count; i++) {
            file_name.push_back(to_string(i));
            all_file.insert(to_string(i));
        }
        cout << "\nNow there are " << file_name.size() << " runs." << endl;
        while (file_name.size() > 1) {
            vector<string> new_file_name;
            for (int i = 0; i < file_name.size(); i += 2) {
                if (i + 1 < file_name.size()) {
                    string l = file_name[i];
                    string r = file_name[i + 1];
                    string t = "merging";
                    twoWayMergeFile(l, r, t);
                    remove(("tmp_" + l).c_str());
                    rename(("tmp_" + t).c_str(), ("tmp_" + l).c_str());
                    remove(("tmp_" + t).c_str());
                    t = l;
                    new_file_name.push_back(t);
                    all_file.insert(t);
                } else {
                    new_file_name.push_back(file_name[i]);
                    all_file.insert(file_name[i]);
                }
            }
            file_name = new_file_name;
            cout << "\nNow there are " << file_name.size() << " runs." << endl;
        }
        /*rename(("tmp_" + file_number + "_" + file_name[0]).c_str(),
               ("sorted" + file_number + ".bin").c_str());*/
        ifstream fin("tmp_" + file_name[0], ios::binary);
        // cerr << file_name[0] << endl;
        // assert(fin.is_open());
        ofstream fout("ordered" + file_number + ".bin", ios::binary);
        StudentData student;
        while (fin.read((char *)&student, sizeof(StudentData))) {
            fout.write((char *)&student, sizeof(StudentData));
        }
        fin.close();
        fout.close();
        for (auto &file : all_file) {
            remove(("tmp_" + file).c_str());
        }
        // remove(("tmp_" + file_name[0]).c_str());
    }

    void printOffset() {
        ifstream fin("ordered" + file_number + ".bin", ios::binary);
        StudentData student;
        int offset = 0;
        int count = 0;
        float prev_weight = -1;
        while (fin.read((char *)&student, sizeof(StudentData))) {
            if (count == 0 || fabs(student.weight - prev_weight) > 1e-6) {
                cout << "\n[" << ++count << "] (" << student.weight << ", " << offset << ")";
            }
            prev_weight = student.weight;
            offset = fin.tellg() / sizeof(StudentData);
        }
        cout << endl;
        fin.close();
    }
};

class Solution {
    FileHandler fileHandler;

   public:
    void WriteCase1Menu() {
        cout << "\n########################################################"
                "\nMission 1: External merge sort "
                "\n########################################################\n";
    }

    void WriteCase2Menu() {
        cout << "\n\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
                "\nMission 2: Build the primary index"
                "\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
                "\n\n<Primary index>: (key, offset)";
    }

    void case1() {
        fileHandler.clear();
        WriteCase1Menu();
        int read_result = fileHandler.read();
        while (read_result == -1) {
            read_result = fileHandler.read();
        }
        if (read_result == -2) return;
        auto start = chrono::high_resolution_clock::now();
        fileHandler.splitData();
        cout << "\nThe internal sort is completed. Check the initial sorted runs!" << endl;
        auto end = chrono::high_resolution_clock::now();
        int64_t split_duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
        start = chrono::high_resolution_clock::now();
        fileHandler.mergeFile();
        end = chrono::high_resolution_clock::now();
        int64_t merge_duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
        cout << "\nThe execution time ...";
        cout << "\nInternal Sort = " << fixed << setprecision(3) << (float)split_duration / 1000 << " ms";
        cout << "\nExternal Sort = " << (float)merge_duration / 1000 << " ms";
        cout << "\nTotal Execution Time = " << (float)(split_duration + merge_duration) / 1000 << " ms"
             << endl;
        cout.unsetf(ios::fixed);
    }

    void case2() {
        if (fileHandler.empty()) return;
        WriteCase2Menu();
        fileHandler.printOffset();
    }
};
void WriteMenu() {
    cout << "\n*** The buffer size is " << MAX_BUFFER_SIZE
         << "\n***********************************************"
            "\n On-machine Exercise 05                       *"
            "\n Mission 1: External Merge Sort on a Big File *"
            "\n Mission 2: Construction of Primary Index     *"
            "\n***********************************************";
}

signed main() {
    CompileErr0r_is_the_weakest_hacker;
    string command;
    Solution sol;
    // use string to avoid malicious input

    // cin.ignore();
    do {
        WriteMenu();
        sol.case1();
        sol.case2();
        cout << "\n[0]Quit or [Any other key]continue?\n";
        cin >> command;
    } while (command != "0");
    //    WriteMenu();

    // cerr << "Time: " << (double)clock() / (double)CLOCKS_PER_SEC << '\n';
    return 0;
}
