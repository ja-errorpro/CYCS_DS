// 11127137 黃乙家, 11127150 張睿恩
/****************************************************/
/*  CPP Template for School                         */
/*  Author: CompileErr0r(YiJia)                     */
/*  Author ID: 11127137                             */
/*  Compile Environment: Linux 5.15.90.1 WSL x86_64 */
/*  Compiler: g++ 9.4                               */
/****************************************************/

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <new>
#include <sstream>
#include <string>
#include <vector>

// #include <bits/stdc++.h>
using namespace std;

#define endl '\n'

template <typename... rest>
void VERBOSE(rest... args) {
#ifdef CompileErr0rDEBUGGING
    cout << "\033[1;37m[\033[1;33mDEBUG\033[1;37m]\033[0m ";
    initializer_list<int>{(cout << args, 0)...};
#endif
}

struct StudentData {
    char student_id[10];
    char student_name[10];
    unsigned char score[6];
    float average_score;
    StudentData() : average_score(0) {
        // memset(student_id, 0, sizeof(student_id));
        // memset(student_name, 0, sizeof(student_name));
        // memset(score, 0, sizeof(score));
    }
};
int stoi(const string &str) {
    string tmp;
    for (char c : str) {
        if (isdigit(c)) tmp += c;
    }
    return atoi(tmp.c_str());
}

float stof(const string &str) {
    string tmp;
    for (char c : str) {
        if (isdigit(c) || c == '.') tmp += c;
    }
    return std::stof(tmp.c_str());
}

int transformTextToBin(string file_number) {
    string file_name = "input" + file_number + ".txt";
    string output_file_name = "input" + file_number + ".bin";
    ifstream fin(file_name);

    if (!fin.is_open()) {
        cout << "\n### " << file_name << " does not exist! ###" << endl;
        file_name.clear();
        return -1;
    }

    // vector<StudentData> student_data;
    ofstream fout(output_file_name, ios::out | ios::binary);
    string tmp;

    while (getline(fin, tmp)) {
        stringstream ss(tmp);
        StudentData current_student;
        vector<string> current_line_data;
        while (getline(ss, tmp, '\t')) current_line_data.push_back(tmp);
        int len = current_line_data.size();
        if (len > 0) strncpy(current_student.student_id, current_line_data[0].c_str(), 10);
        // should erase all the space in the name

        if (len > 1) strncpy(current_student.student_name, current_line_data[1].c_str(), 10);
        // fout.write((char *)&current_student.student_name, strlen(current_student.student_name));
        for (int i = 0; i < 6; i++) {
            if (i + 2 < len)
                current_student.score[i] = (unsigned char)::stoi(current_line_data[i + 2]);
            else
                current_student.score[i] = 0;
            // fout.write((char *)&current_student.score[i], sizeof(unsigned char));
        }
        if (len > 8) current_student.average_score = ::stof(current_line_data[len - 1]);
        // fout.write((char *)&current_student.average_score, sizeof(float));
        fout.write((char *)&current_student, sizeof(StudentData));
    }

    fin.close();

    fout.close();
    return 0;
}

class MinPrimeSearcher {
    vector<bool> isPrime; // for sieve of eratosthenes
    void _initEratosthenes() {
        isPrime.resize(1000000, true);
        isPrime[0] = isPrime[1] = false;
        for (int i = 2; i < 1000000; i++) {
            if (isPrime[i]) {
                for (int j = i * 2; j < 1000000; j += i) {
                    isPrime[j] = false;
                }
            }
        }
    }

   public:
    /*
        get a prime number that is larger than the size
        @param size: the size of the table
        @return: the prime number
    */
    int getMinPrime(int size) {
        if (isPrime.empty()) _initEratosthenes();
        if (size <= 2) return 2;
        if (size < 1000000) {
            for (int i = size; i < 1000000; i++) {
                if (isPrime[i]) return i;
            }

            // cannot find a prime number that less than 1000000, then use brute force
        }

        for (int i = size; i < 100000000; i++) {
            bool iisPrime = true;
            for (int j = 2; j * j <= i; j++) {
                if (i % j == 0) {
                    iisPrime = false;
                    break;
                }
            }
            if (iisPrime) return i;
        }

        return 0;
    }
} minPrimeSearcher;

class QuadraticProbingHashTable {
    vector<pair<int, int>> table; // index, hash value
    int hash_table_size;
    int origin_data_size;
    int total_success;
    int total_failure;

    int _insert(string key, int data) {
        int index = hash(key);
        pair<int, int> tmp = make_pair(data, index);
        int i = 1;
        int original_index = index;
        while (table[index].first != -1) {
            index = (original_index % hash_table_size +
                     (i % hash_table_size) * (i % hash_table_size) % hash_table_size) %
                    hash_table_size;
            i++;
        }
        table[index] = tmp;
        return i;
    }

   public:
    QuadraticProbingHashTable()
        : origin_data_size(0), hash_table_size(0), total_success(0), total_failure(0) {}
    QuadraticProbingHashTable(int size) : origin_data_size(size), total_success(0), total_failure(0) {
        this->hash_table_size = minPrimeSearcher.getMinPrime((int)ceil(1.15 * origin_data_size));
        table.resize(this->hash_table_size, make_pair(-1, -1));
    }
    ~QuadraticProbingHashTable() { clear(); }
    int hash(string key) {
        int sum = 1;
        int len = key.size();
        for (int i = 0; i < len; i++) {
            sum = sum * key[i] % hash_table_size;
            // cerr << "sum: " << sum << endl;
        }
        return sum % hash_table_size;
    }
    void insert(string key, int data) {
        int success_search_cnt = _insert(key, data);
        total_success += success_search_cnt;
    }
    int countFailedSearch(int index) {
        int original_index = index;
        int cnt = 1;
        while (table[index].first != -1) {
            index = ((original_index % hash_table_size) +
                     (cnt % hash_table_size) * (cnt % hash_table_size) % hash_table_size) %
                    hash_table_size;
            // cerr << "Failed search: " << index << endl;
            cnt++;
        }
        total_failure += cnt;
        // cerr << "Search count: " << total_failure << endl;
        return cnt;
    }

    void calculateAvergeFailedCount() {
        total_failure = 0;
        for (int i = 0; i < hash_table_size; i++) {
            countFailedSearch(i);
        }
        total_failure -= hash_table_size;
    }

    vector<pair<int, int>> getTable() { return table; }

    void printStatistics() {
        cout << fixed << setprecision(4) << "unsuccessful search: " << (float)total_failure / hash_table_size
             << " comparisons on average" << endl;

        cout << "\nsuccessful search: " << (float)total_success / origin_data_size
             << " comparisons on average" << endl;
    }

    void clear() {
        table.clear();
        origin_data_size = 0;
        hash_table_size = 0;
        total_success = 0;
        total_failure = 0;
    }
};

class DoubleHash {
    vector<pair<StudentData, int>> table; // data, hash value
    int hash_table_size;
    int origin_data_size;
    int total_success;
    int maxStep;

    int _insert(string key, StudentData data) {
        int index = hash(key);
        pair<StudentData, int> tmp = make_pair(data, index);
        int success_search_count = 1;
        int original_index = index;
        int step = 1;
        int len = key.size();
        for (int i = 0; i < len; i++) {
            step = step * key[i] % maxStep;
        }
        step = maxStep - step % maxStep;

        while (table[index].second != -1) {
            index = (index + step) % hash_table_size;
            success_search_count++;
        }
        table[index] = tmp;
        return success_search_count;
    }

   public:
    DoubleHash() : origin_data_size(0), hash_table_size(0), total_success(0), maxStep(0) {}
    DoubleHash(int size) : origin_data_size(size), total_success(0) {
        this->hash_table_size = minPrimeSearcher.getMinPrime((int)ceil(1.15 * origin_data_size));
        table.resize(this->hash_table_size, make_pair(StudentData(), -1));
        maxStep = minPrimeSearcher.getMinPrime(ceil((float)origin_data_size / 5));
    }
    int hash(string key) {
        int sum = 1;
        int len = key.size();
        for (int i = 0; i < len; i++) {
            sum = sum * key[i] % hash_table_size;
            // cerr << "sum: " << sum << endl;
        }
        return sum % hash_table_size;
    }
    void insert(string key, StudentData data) {
        int success_search_cnt = _insert(key, data);
        total_success += success_search_cnt;
    }

    vector<pair<StudentData, int>> getTable() { return table; }

    void printStatistics() {
        cout << "successful search: " << (float)total_success / origin_data_size << " comparisons on average"
             << endl;
    }

    void clear() {
        table.clear();
        origin_data_size = 0;
        hash_table_size = 0;
        total_success = 0;
        maxStep = 0;
    }

    ~DoubleHash() { clear(); }
};

class Data {
    string input_file_name;
    string quadratic_output_file_name;
    string file_number;
    vector<StudentData> original_student_data;
    QuadraticProbingHashTable quadratic_hash_table;
    DoubleHash double_hash_table;

   public:
    Data() {}
    ~Data() { clear(); }
    void clear() {
        file_number.clear();
        input_file_name.clear();
        quadratic_output_file_name.clear();
        original_student_data.clear();
        quadratic_hash_table.clear();
        double_hash_table.clear();
    }
    bool isEmpty() { return original_student_data.empty(); }
    int read() {
        if (input_file_name.empty()) {
            cout << "\nInput a file number ([0] Quit): ";
            cin >> file_number;
            cin.ignore();
            if (file_number == "0") return -2;
            input_file_name = "input" + file_number + ".bin";
        }
        ifstream fin(input_file_name);
        int transformed = 0;
        if (!fin.is_open()) {
            cout << "\n### " << input_file_name << " does not exist! ###" << endl;
            transformed = transformTextToBin(file_number);
        }
        if (transformed == -1) return transformed;
        fin.close();
        return 0;
    }

    void readData() {
        ifstream fin(input_file_name, ios::binary);
        StudentData tmp;
        while (fin.read((char *)&tmp, sizeof(StudentData))) {
            original_student_data.push_back(tmp);
        }
        fin.close();
    }

    void buildQuadratic() {
        quadratic_hash_table = QuadraticProbingHashTable(original_student_data.size());
        for (int i = 0; i < original_student_data.size(); i++) {
            // cerr << "Inserting: " << original_student_data[i].student_id << endl;
            // cerr << "Hash: " << hash_table.hash(original_student_data[i].student_id) << endl;
            string key = original_student_data[i].student_id;
            quadratic_hash_table.insert(key, i);
        }
    }

    void printQuadraticStatistics() {
        quadratic_hash_table.calculateAvergeFailedCount();
        quadratic_hash_table.printStatistics();
    }

    void writeQuadraticHashTable() {
        vector<pair<int, int>> table = quadratic_hash_table.getTable();
        quadratic_output_file_name = "quadratic" + file_number + ".txt";
        ofstream fout(quadratic_output_file_name);
        fout << " --- Hash table created by Quadratic probing ---\n";
        for (int i = 0; i < table.size(); i++) {
            if (table[i].first != -1) {
                int index = table[i].first;
                fout << "[" << setw(3) << i << "] ";
                fout << setw(10) << table[i].second << ", " << setw(10)
                     << original_student_data[index].student_id << ", " << setw(10)
                     << original_student_data[index].student_name << ", " << setw(10)
                     << original_student_data[index].average_score << endl;
            } else
                fout << "[" << setw(3) << i << "] " << endl;
        }
        fout << " ----------------------------------------------------- \n";
        fout.close();
    }

    void buildDoubleHashTable() {
        double_hash_table = DoubleHash(original_student_data.size());
        for (int i = 0; i < original_student_data.size(); i++) {
            string key = original_student_data[i].student_id;
            double_hash_table.insert(key, original_student_data[i]);
        }
    }

    void printDoubleStatistics() { double_hash_table.printStatistics(); }

    void writeDoubleHashTable() {
        vector<pair<StudentData, int>> table = double_hash_table.getTable();
        string double_output_file_name = "double" + file_number + ".txt";
        ofstream fout(double_output_file_name);
        fout << " --- Hash table created by Double hashing    ---\n";
        for (int i = 0; i < table.size(); i++) {
            if (table[i].second != -1) {
                int index = table[i].second;
                fout << "[" << setw(3) << i << "] ";
                fout << setw(10) << index << ", " << setw(10) << table[i].first.student_id << ", " << setw(10)
                     << table[i].first.student_name << ", " << setw(10) << table[i].first.average_score
                     << endl;
            } else
                fout << "[" << setw(3) << i << "] " << endl;
        }
        fout << " ----------------------------------------------------- \n";
        fout.close();
    }
};

class Solution {
    Data data;

   public:
    Solution() {}
    void case1() {
        data.clear();
        int state = data.read();
        if (state < 0) return;
        data.readData();
        data.buildQuadratic();
        cout << "\nHash table has been successfully created by Quadratic probing" << endl;
        data.printQuadraticStatistics();
        data.writeQuadraticHashTable();
    }

    void case2() {
        if (data.isEmpty()) {
            cout << "### Command 1 first. ###" << endl;
            return;
        }
        data.buildDoubleHashTable();
        cout << "\nHash table has been successfully created by Double hashing" << endl;
        data.printDoubleStatistics();
        data.writeDoubleHashTable();
    }
};
void WriteMenu() {
    cout << "\n******* Hash Table *****\n"
            "* 0. QUIT              *\n"
            "* 1. Quadratic probing *\n"
            "* 2. Double hashing    *\n"
            "************************\n"
            "Input a choice(0, 1, 2): ";
}
signed main() {
    string command;
    Solution sol;

    // use string to avoid malicious input
    WriteMenu();
    while (cin >> command && command != "0") {
        cin.ignore();
        if (command == "1") {
            sol.case1();
            // cerr << "\033[1;32mTask Passed\033[0m" << endl;
        } else if (command == "2") {
            sol.case2();
            // cerr << "\033[1;32mTask Passed\033[0m" << endl;
        } else
            cout << "\nCommand does not Exist!!!" << endl;
        WriteMenu();
    }
    // cerr << "Time: " << (double)clock() / (double)CLOCKS_PER_SEC << '\n';
    return 0;
}
