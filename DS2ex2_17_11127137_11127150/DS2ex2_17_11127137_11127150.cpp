// 11127137 ¶À¤A®a, 11127150 ±iºÍ®¦
/****************************************************/
/*  CPP Template for School                         */
/*  Author: CompileErr0r(YiJia)                     */
/*  Author ID: 11127137                             */
/*  Compile Environment: Linux 5.15.90.1 WSL x86_64 */
/*  Compiler: g++ 9.4                               */
/****************************************************/

#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

// #include<bits/extc++.h>
using namespace std;

#define endl '\n'

// #define CompileErr0rDEBUGGING

template <typename... rest>
void VERBOSE(rest... args) {
#ifdef CompileErr0rDEBUGGING
    // cout << "\033[1;37m[\033[1;33mDEBUG\033[1;37m]\033[0m ";
    initializer_list<int>{(cout << args, 0)...};
#endif
}

template <class T>
class two3Tree {};

template <class T>
class AVL {};

class Data {
    struct _data {
        int school_id;
        string school_name;
        int department_id;
        string department_name;
        string day_further;
        string level;
        int student_count;
        int teacher_count;
        int graduate_count;
    };
    vector<_data> _data_arr;

    string _filename;

    void _clear() { _data_arr.clear(); }

   public:
    Data() {}
    ~Data() { _clear(); }
    void reset() {
        _clear();
        _filename.clear();
    }

    bool isDigit(const string &str) {
        for (char c : str) {
            if (!isdigit(c)) return false;
        }
        return true;
    }

    /*
        Convert string to integer.
        To avoid the invalid conversion, the method will only convert the digits in the string.
        "123abc456" -> "123456" -> 123456
        "1,234,567" -> "1234567" -> 1234567
        @param str: the string to be converted
        @return: the integer converted from the string
    */
    int stoi(const string &str) {
        string tmp;
        for (char c : str) {
            if (isdigit(c)) tmp += c;
        }
        return atoi(tmp.c_str());
    }

    bool isEmpty() const { return _data_arr.empty(); }
    /*
        Read data from file
        @return: 1 for success, 2 for quit, -1 for fail
        @side effect: update _data_arr, _data_hash_table, _bst_by_hp, _maxheap_by_hp, _filename
    */
    int read() {
        if (_filename.empty()) {
            cout << "\nInput a file number ([0] Quit): ";
            cin >> _filename;
            cin.ignore();
            if (_filename == "0") return 2;
            _filename = "input" + _filename + ".txt";
        }
        ifstream fin(_filename);
        if (!fin.is_open()) {
            cout << "\n### " << _filename << " does not exist! ###" << endl;
            _filename.clear();
            return -1;
        }

        _clear();
        string tmp;
        getline(fin, tmp); // skip the lines
        getline(fin, tmp);
        getline(fin, tmp);

        while (getline(fin, tmp)) {
            stringstream ss(tmp);
            _data data;
            vector<string> read_line_data_tmp;
            string line_tmp;
            while (getline(ss, line_tmp, '\t')) read_line_data_tmp.push_back(line_tmp); // split by tab
            int len = read_line_data_tmp.size();
            data.school_id = (len > 0) ? stoi(read_line_data_tmp[0]) : 0;
            data.school_name = (len > 1) ? read_line_data_tmp[1] : "";
            data.department_id = (len > 2) ? stoi(read_line_data_tmp[2]) : 0;
            data.department_name = (len > 3) ? read_line_data_tmp[3] : "";
            data.day_further = (len > 4) ? read_line_data_tmp[4] : "";
            data.level = (len > 5) ? read_line_data_tmp[5] : "";
            data.student_count = (len > 6) ? stoi(read_line_data_tmp[6]) : 0;
            data.teacher_count = (len > 7) ? stoi(read_line_data_tmp[7]) : 0;
            data.graduate_count = (len > 8) ? stoi(read_line_data_tmp[8]) : 0;
            _data_arr.push_back(data);
        }

        fin.close();
        return 1;
    }

}; // class Data

class Solution {
    Data _ds;

   public:
    void case1() {
        _ds.reset();
        int state = _ds.read();
        while (state < 1) {
            state = _ds.read();
        }
        if (state == 1) {
        }
    }
    void case2() {
        _ds.reset();
        int state = _ds.read();
        while (state < 1) {
            state = _ds.read();
        }
        if (state == 1) {
        }
    }
};

void WriteMenu() {
    cout << "**** Balanced Search Trees ****\n"
            "* 0. QUIT                     *\n"
            "* 1. Build 23 tree            *\n"
            "* 2. Build AVL tree           *\n"
            "*******************************\n"
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
        }
#ifdef CompileErr0rDEBUGGING
        else if (command == "3")
            sol.case3();

        else if (command == "4")
            sol.case4();
        else if (command == "5")
            sol.case5();
        else if (command == "6")
            sol.case6();
        else if (command == "7")
            sol.case7();
#endif
        else
            cout << "\nCommand does not Exist!!!" << endl;
        WriteMenu();
    }
    // cerr << "Time: " << (double)clock() / (double)CLOCKS_PER_SEC << '\n';
    return 0;
}
