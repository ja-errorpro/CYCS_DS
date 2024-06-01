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

struct PrimaryIndex {
    float weight;
    int offset;
    PrimaryIndex() : weight(0), offset(0) {}
};

class FileHandler {
   private:
    string input_file_name;
    string file_number;
    vector<StudentData> partial_student_data;
    vector<PrimaryIndex> primary_index;
    int split_count;

   public:
    int64_t internal_sort_duration;
    int64_t external_sort_duration;
    FileHandler() : split_count(0), internal_sort_duration(0), external_sort_duration(0) {}
    ~FileHandler() { clear(); }
    void clear() {
        primary_index.clear();
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

    void floatRadixSort(vector<StudentData> &data) {
        for (int i = 0; i < data.size(); ++i) {
            reinterpret_cast<int &>(data[i].weight) = reinterpret_cast<int &>(data[i].weight) | 0x80000000;
        }
        vector<StudentData> bucket[256];
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < data.size(); ++j) {
                int index = (reinterpret_cast<int &>(data[j].weight) >> (i * 8)) & 0xff;
                bucket[index].push_back(data[j]);
            }
            int index = 0;
            for (int j = 0; j < 256; ++j) {
                for (int k = 0; k < bucket[j].size(); ++k) {
                    data[index++] = bucket[j][k];
                }
                bucket[j].clear();
            }
        }
        for (int i = 0; i < data.size(); ++i) {
            reinterpret_cast<int &>(data[i].weight) = reinterpret_cast<int &>(data[i].weight) & 0x7fffffff;
        }
        reverse(data.begin(), data.end());
    }

    void splitData() {
        ifstream fin(input_file_name, ios::binary);
        calculateSplitCount();
        internal_sort_duration = 0;
        for (int i = 0; i < split_count; i++) {
            partial_student_data.clear();
            for (int j = 0; j < MAX_BUFFER_SIZE; j++) {
                StudentData student;
                fin.read((char *)&student, sizeof(StudentData));
                if (fin.eof()) break;
                partial_student_data.push_back(student);
            }
            auto start = chrono::high_resolution_clock::now();
            stable_sort(
                partial_student_data.begin(), partial_student_data.end(),
                [](const StudentData &a, const StudentData &b) { return a.weight - b.weight > 1e-6; });
            // floatRadixSort(partial_student_data);
            auto end = chrono::high_resolution_clock::now();
            int64_t duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
            internal_sort_duration += duration;
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

    void twoWayMergeFileBuffer(string left_file, string right_file, string tmp_file, int buffer_size) {
        ifstream left_fin("tmp_" + left_file, ios::binary);
        ifstream right_fin("tmp_" + right_file, ios::binary);
        ofstream fout("tmp_" + tmp_file, ios::binary);
        StudentData *left_student = new StudentData[buffer_size];
        StudentData *right_student = new StudentData[buffer_size];
        StudentData *out_student = new StudentData[buffer_size * 2];
        left_fin.read((char *)left_student, buffer_size * sizeof(StudentData));
        right_fin.read((char *)right_student, buffer_size * sizeof(StudentData));
        int l = 0, r = 0;
        int out = 0;
        while (l < buffer_size && r < buffer_size) {
            if (left_student[l].weight >= right_student[r].weight) {
                out_student[out] = left_student[l];
                l++;

            } else {
                out_student[out] = right_student[r];
                r++;
            }
            out++;
        }
        while (l < buffer_size) {
            out_student[out] = left_student[l];
            l++;
            out++;
        }
        while (r < buffer_size) {
            out_student[out] = right_student[r];
            r++;
            out++;
        }
        if (out > 0) {
            fout.write((char *)out_student, out * sizeof(StudentData));
        }
        delete[] left_student;
        delete[] right_student;
        delete[] out_student;
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
        external_sort_duration = 0;
        cout << "\nNow there are " << file_name.size() << " runs." << endl;
        int level = 1;
        remove(("order" + file_number + ".bin").c_str());
        while (file_name.size() > 1) {
            vector<string> new_file_name;
            for (int i = 0; i < file_name.size(); i += 2) {
                if (i + 1 < file_name.size()) {
                    string l = file_name[i];
                    string r = file_name[i + 1];
                    string t = "merging";
                    int buffer_size = level * MAX_BUFFER_SIZE;
                    auto start = chrono::high_resolution_clock::now();
                    twoWayMergeFile(l, r, t);
                    // twoWayMergeFileBuffer(l, r, t, buffer_size);
                    auto end = chrono::high_resolution_clock::now();
                    int64_t duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
                    external_sort_duration += duration;
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
            level++;
            file_name = new_file_name;
            cout << "\nNow there are " << file_name.size() << " runs." << endl;
        }
        rename(("tmp_" + file_name[0]).c_str(), ("order" + file_number + ".bin").c_str());

        /*ifstream fin("tmp_" + file_name[0], ios::binary);
        // cerr << file_name[0] << endl;
        assert(fin.is_open());
        ofstream fout("order" + file_number + ".bin", ios::binary);
        assert(fout.is_open());
        StudentData student;
        while (fin.read((char *)&student, sizeof(StudentData))) {
            fout.write((char *)&student, sizeof(StudentData));
        }
        fin.close();
        fout.close();*/
        for (auto &file : all_file) {
            remove(("tmp_" + file).c_str());
        }
        remove(("tmp_" + file_name[0]).c_str());
    }

    void printOffset() {
        ifstream fin("order" + file_number + ".bin", ios::binary);

        int offset = 0;
        int count = 0;
        float prev_weight = -1;
        StudentData *student = new StudentData[MAX_BUFFER_SIZE];

        // read the first block
        fin.read((char *)student, MAX_BUFFER_SIZE * sizeof(StudentData));
        int block_count = 0;
        while (!fin.eof()) {
            for (int i = 0; i < MAX_BUFFER_SIZE; i++) {
                // cerr << student[i].weight << endl;
                if (count == 0 || fabs(student[i].weight - prev_weight) > 1e-6) {
                    PrimaryIndex index;
                    index.weight = student[i].weight;
                    index.offset = offset;
                    primary_index.push_back(index);
                    prev_weight = student[i].weight;
                    count++;
                }
                offset = 1 + i + block_count * MAX_BUFFER_SIZE;
            }
            block_count++;
            fin.read((char *)student, MAX_BUFFER_SIZE * sizeof(StudentData));
        }
        // print the primary index
        for (int i = 0; i < primary_index.size(); i++) {
            cout << "\n[" << i + 1 << "] (" << primary_index[i].weight << ", " << primary_index[i].offset
                 << ")";
        }
        /*while (fin.read((char *)&student, sizeof(StudentData))) {
            if (count == 0 || fabs(student.weight - prev_weight) > 1e-6) {
                cout << "\n[" << ++count << "] (" << student.weight << ", " << offset << ")";
            }
            prev_weight = student.weight;
            offset = fin.tellg() / sizeof(StudentData);
        }*/

        delete[] student;

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
            fileHandler.clear();
            read_result = fileHandler.read();
        }
        if (read_result == -2) return;
        // auto start = chrono::high_resolution_clock::now();
        fileHandler.splitData();
        cout << "\nThe internal sort is completed. Check the initial sorted runs!" << endl;
        // auto end = chrono::high_resolution_clock::now();
        // int64_t split_duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
        // start = chrono::high_resolution_clock::now();
        fileHandler.mergeFile();
        // end = chrono::high_resolution_clock::now();
        // int64_t merge_duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
        cout << "\nThe execution time ...";
        cout << "\nInternal Sort = " << fixed << setprecision(3)
             << (float)fileHandler.internal_sort_duration / 1000 << " ms";
        cout << "\nExternal Sort = " << (float)fileHandler.external_sort_duration / 1000 << " ms";
        cout << "\nTotal Execution Time = "
             << (float)(fileHandler.internal_sort_duration + fileHandler.external_sort_duration) / 1000
             << " ms" << endl;
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
