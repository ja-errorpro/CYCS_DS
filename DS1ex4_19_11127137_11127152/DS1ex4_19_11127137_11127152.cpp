// 11127137, ¶À¤A®a
/****************************************************/
/*  CPP Template for School                         */
/*  Author: CompileErr0r(YiJia)                     */
/*  Author ID: 11127137                             */
/*  Compile Environment: Linux 5.15.90.1 WSL x86_64 */
/*  Compiler: g++ 9.4                               */
/****************************************************/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <new>
#include <sstream>
#include <vector>

// #include <bits/stdc++.h>
using namespace std;

#define endl '\n'

// #define CompileErr0rDEBUGGING

template <typename... rest>
void VERBOSE(rest... args) {
#ifdef CompileErr0rDEBUGGING
    cout << "\033[1;37m[\033[1;33mDEBUG\033[1;37m]\033[0m ";
    initializer_list<int>{(cout << args, 0)...};
#endif
}

template <class T>
class BST {
   private:
    struct _TNode {
        T data;
        _TNode *left, *right;
        _TNode(const T &d, _TNode *l = nullptr, _TNode *r = nullptr) : data(d), left(l), right(r) {}
    };
    _TNode *root;
    int visited_count;
    _TNode *min(_TNode *cur_ptr) {
        if (cur_ptr == nullptr) return nullptr;
        while (cur_ptr->left != nullptr) cur_ptr = cur_ptr->left;
        return cur_ptr;
    }
    _TNode *max(_TNode *cur_ptr) {
        if (cur_ptr == nullptr) return nullptr;
        while (cur_ptr->right != nullptr) cur_ptr = cur_ptr->right;
        return cur_ptr;
    }
    _TNode *insert(_TNode *cur_ptr, const T &data) {
        if (cur_ptr == nullptr) return new _TNode(data);
        if (data < cur_ptr->data)
            cur_ptr->left = insert(cur_ptr->left, data);
        else
            cur_ptr->right = insert(cur_ptr->right, data);
        return cur_ptr;
    }
    _TNode *query(_TNode *cur_ptr, const T &data) {
        if (cur_ptr == nullptr) return nullptr;
        if (data == cur_ptr->data) return cur_ptr;
        if (data < cur_ptr->data)
            return query(cur_ptr->left, data);
        else
            return query(cur_ptr->right, data);
    }
    _TNode *erase(_TNode *cur_ptr, const T &data) {
        if (cur_ptr == nullptr) return nullptr;
        if (data < cur_ptr->data)
            cur_ptr->left = erase(cur_ptr->left, data);
        else if (data > cur_ptr->data)
            cur_ptr->right = erase(cur_ptr->right, data);
        else {
            if (cur_ptr->left == nullptr) {
                _TNode *tmp = cur_ptr->right;
                delete cur_ptr;
                return tmp;
            } else if (cur_ptr->right == nullptr) {
                _TNode *tmp = cur_ptr->left;
                delete cur_ptr;
                return tmp;
            }
            _TNode *tmp = min(cur_ptr->right);
            cur_ptr->data = tmp->data;
            cur_ptr->right = erase(cur_ptr->right, tmp->data);
        }
        return cur_ptr;
    }
    _TNode *clear(_TNode *cur_ptr) {
        if (cur_ptr == nullptr) return nullptr;
        clear(cur_ptr->left);
        clear(cur_ptr->right);
        delete cur_ptr;
        return nullptr;
    }
    vector<T> preOrder(_TNode *cur_ptr) {
        vector<T> ans;
        if (cur_ptr == nullptr) return ans;
        vector<T> left = preOrder(cur_ptr->left);
        vector<T> right = preOrder(cur_ptr->right);
        ans.push_back(cur_ptr->data);
        ans.insert(ans.end(), left.begin(), left.end());
        ans.insert(ans.end(), right.begin(), right.end());
        return ans;
    }
    vector<T> inOrder(_TNode *cur_ptr) {
        vector<T> ans;
        if (cur_ptr == nullptr) return ans;
        vector<T> left = inOrder(cur_ptr->left);
        vector<T> right = inOrder(cur_ptr->right);
        ans.insert(ans.end(), left.begin(), left.end());
        ans.push_back(cur_ptr->data);
        ans.insert(ans.end(), right.begin(), right.end());
        return ans;
    }
    vector<T> postOrder(_TNode *cur_ptr) {
        vector<T> ans;
        if (cur_ptr == nullptr) return ans;
        vector<T> left = postOrder(cur_ptr->left);
        vector<T> right = postOrder(cur_ptr->right);
        ans.insert(ans.end(), left.begin(), left.end());
        ans.insert(ans.end(), right.begin(), right.end());
        ans.push_back(cur_ptr->data);
        return ans;
    }
    int getHeight(_TNode *cur_ptr) {
        if (cur_ptr == nullptr) return 0;
        return std::max(getHeight(cur_ptr->left), getHeight(cur_ptr->right)) + 1;
    }
    void queryAll(_TNode *cur_ptr, const T &data, vector<T> &ans) {
        if (cur_ptr == nullptr) return;
        if (data == cur_ptr->data) {
            ans.push_back(cur_ptr->data);
            queryAll(cur_ptr->left, data, ans);
            queryAll(cur_ptr->right, data, ans);
        } else if (data < cur_ptr->data) {
            queryAll(cur_ptr->left, data, ans);
        } else {
            queryAll(cur_ptr->right, data, ans);
        }
    }
    void queryAllLowerBound(_TNode *cur_ptr, const T &data, vector<T> &ans) {
        if (cur_ptr == nullptr) return;
        if (data <= cur_ptr->data) {
            ans.push_back(cur_ptr->data);
            queryAllLowerBound(cur_ptr->left, data, ans);
            queryAllLowerBound(cur_ptr->right, data, ans);
        } else {
            queryAllLowerBound(cur_ptr->right, data, ans);
        }
    }

   public:
    BST() : root(nullptr), visited_count(0) {}
    ~BST() {
        clear();

        VERBOSE("Destructor finished", endl);
    }
    void insert(const T &data) {
        root = insert(root, data);
        // VERBOSE("Insert function finished", endl);
    }
    void erase(const T &data) { root = erase(root, data); }
    void clear() { root = clear(root); }
    bool empty() const { return root == nullptr; }
    vector<T> preOrder() { return preOrder(root); }
    vector<T> inOrder() { return inOrder(root); }
    vector<T> postOrder() { return postOrder(root); }
    int getHeight() { return getHeight(root); }

    vector<T> queryAllLowerBound(const T &data) {
        vector<T> ans;
        queryAllLowerBound(root, data, ans);
        return ans;
    }
    vector<T> queryAll(const T &data) {
        vector<T> ans;
        queryAll(root, data, ans);
        return ans;
    }

    vector<T> getInOrder() { return inOrder(root); }
    vector<T> getPreOrder() { return preOrder(root); }
    vector<T> getPostOrder() { return postOrder(root); }
};

class Dataset {
    struct _data {
        string school_name;
        string department_name;
        string day_further;
        string level;
        int student_count;
        int teacher_count;
        int graduate_count;
    };
    struct _data_cmp_by_graduate_count {
        _data data;
        bool operator<(_data_cmp_by_graduate_count b) const {
            return data.graduate_count < b.data.graduate_count;
        }
        bool operator==(_data_cmp_by_graduate_count b) const {
            return data.graduate_count == b.data.graduate_count;
        }
        bool operator<=(_data_cmp_by_graduate_count b) const {
            return data.graduate_count <= b.data.graduate_count;
        }
        bool operator>(_data_cmp_by_graduate_count b) const {
            return data.graduate_count > b.data.graduate_count;
        }
        bool operator>=(_data_cmp_by_graduate_count b) const {
            return data.graduate_count >= b.data.graduate_count;
        }
    };
    struct _data_cmp_by_school_name {
        _data data;
        bool operator<(_data_cmp_by_school_name b) const { return data.school_name < b.data.school_name; }
        bool operator==(_data_cmp_by_school_name b) const { return data.school_name == b.data.school_name; }
        bool operator<=(_data_cmp_by_school_name b) const { return data.school_name <= b.data.school_name; }
        bool operator>(_data_cmp_by_school_name b) const { return data.school_name > b.data.school_name; }
        bool operator>=(_data_cmp_by_school_name b) const { return data.school_name >= b.data.school_name; }
    };
    vector<_data> _data_arr;
    BST<_data_cmp_by_graduate_count> _bst_by_graduate_count;
    BST<_data_cmp_by_school_name> _bst_by_school_name;
    string _filename;
    void _insert(const _data &d) {
        _data_arr.push_back(d);
        _bst_by_graduate_count.insert({d});
        _bst_by_school_name.insert({d});
    }
    void _clear() {
        _data_arr.clear();
        _bst_by_graduate_count.clear();
        _bst_by_school_name.clear();
    }

   public:
    Dataset() {}
    ~Dataset() { _clear(); }
    void reset() {
        _clear();
        _filename.clear();
    }
    bool isEmpty() const { return _data_arr.empty(); }
    void read() {
        if (_filename.empty()) {
            cout << "\nInput a file number: ";
            cin >> _filename;
            cin.ignore();
            _filename = "input" + _filename + ".txt";
        }
        ifstream fin(_filename);
        if (!fin.is_open()) {
            cout << "### " << _filename << " does not exist! ###" << endl;
            return;
        }

        _clear();
        string tmp;
        getline(fin, tmp);
        getline(fin, tmp);
        getline(fin, tmp);
        while (getline(fin, tmp)) {
            stringstream ss(tmp);
            _data d;
            string garbage, concat;
            ss >> garbage;
            ss >> d.school_name;
            // VERBOSE("school_name: ", d.school_name, "\t");
            ss >> garbage;
            ss >> d.department_name;
            // VERBOSE("department_name: ", d.department_name, "\t");
            ss >> d.day_further;
            ss >> concat;
            d.day_further += " " + concat;
            // VERBOSE("day_further: ", d.day_further, "\t");
            ss >> d.level;
            ss >> concat;
            d.level += " " + concat;
            // VERBOSE("level: ", d.level, "\t");
            ss >> d.student_count;
            // VERBOSE("student_count: ", d.student_count, "\t");
            ss >> d.teacher_count;
            // VERBOSE("teacher_count: ", d.teacher_count, "\t");
            ss >> d.graduate_count;
            // VERBOSE("graduate_count: ", d.graduate_count, endl);

            _insert(d);
            // VERBOSE("Insert function finished", endl);
        }
        fin.close();
        // VERBOSE("Read file: ", _filename, endl);
    }
    void printHeights() {
        if (_data_arr.empty()) {
            cout << "\nThere is no data!" << endl;
            return;
        }
        int height = _bst_by_school_name.getHeight();
        cout << "Tree height {School name} = " << height << endl;
        height = _bst_by_graduate_count.getHeight();
        cout << "Tree height {Number of graduates} = " << height << endl;
    }
    void printByInOrder() {
        vector<_data_cmp_by_graduate_count> v = _bst_by_graduate_count.getInOrder();
        for (auto &d : v)
            cout << d.data.school_name << '\t' << d.data.department_name << '\t' << d.data.day_further << '\t'
                 << d.data.level << '\t' << d.data.student_count << '\t' << d.data.teacher_count << '\t'
                 << d.data.graduate_count << endl;
    }
    void printBypreOrder() {
        vector<_data_cmp_by_graduate_count> v = _bst_by_graduate_count.getPreOrder();
        for (auto &d : v)
            cout << d.data.school_name << '\t' << d.data.department_name << '\t' << d.data.day_further << '\t'
                 << d.data.level << '\t' << d.data.student_count << '\t' << d.data.teacher_count << '\t'
                 << d.data.graduate_count << endl;
    }
    void printByPostOrder() {
        vector<_data_cmp_by_graduate_count> v = _bst_by_graduate_count.getPostOrder();
        for (auto &d : v)
            cout << d.data.school_name << '\t' << d.data.department_name << '\t' << d.data.day_further << '\t'
                 << d.data.level << '\t' << d.data.student_count << '\t' << d.data.teacher_count << '\t'
                 << d.data.graduate_count << endl;
    }
    int readPositiveNum() {
        string s;
        cin >> s;
        cin.ignore();
        try {
            for (auto c : s)
                if (!isdigit(c)) throw -1;
            int num = stoi(s);
            return num;
        } catch (...) {
            cout << "### the input string " << s << " is not a decimal number! ###" << endl;
            return -1;
        }
    }
    void queryByGraduateCount() {
        if (_data_arr.empty()) {
            cout << "\nThere is no match!" << endl;
            VERBOSE("Dataset is empty", endl);
            return;
        }

        cout << "Input the number of graduates: ";
        int graduate_count = readPositiveNum();
        if (graduate_count == -1) {
            cout << "There is no match!" << endl;
            VERBOSE("Invalid input", endl);
            return;
        }
        vector<_data_cmp_by_graduate_count> ans = _bst_by_graduate_count.queryAllLowerBound({_data{
            .student_count = 0,
            .teacher_count = 0,
            .graduate_count = graduate_count,
        }});
        if (ans.empty()) {
            cout << "There is no match!" << endl;
            VERBOSE("ans is empty", endl);
            return;
        }
        cout << "Search results:" << endl;
        int i = 0;
        for (auto &ad : ans) {
            _data d = ad.data;
            cout << "[" << ++i << "]\t";
            cout << d.school_name << '\t' << d.department_name << '\t' << d.day_further << '\t' << d.level
                 << '\t' << d.student_count << '\t' << d.teacher_count << '\t' << d.graduate_count << endl;
        }
    }

    void queryBySchoolName() {
        if (_data_arr.empty()) {
            cout << "\nThere is no match!" << endl;
            VERBOSE("Dataset is empty", endl);
            return;
        }

        cout << "Input a school name: ";
        string school_name;
        getline(cin, school_name);
        vector<_data_cmp_by_school_name> ans = _bst_by_school_name.queryAll({_data{
            .school_name = school_name,
        }});
        if (ans.empty()) {
            cout << "There is no match!" << endl;
            VERBOSE("ans is empty", endl);
            return;
        }
        cout << "Search results:" << endl;
        int i = 0;
        for (auto &ad : ans) {
            _data d = ad.data;
            cout << "[" << ++i << "]\t";
            cout << d.school_name << '\t' << d.department_name << '\t' << d.day_further << '\t' << d.level
                 << '\t' << d.student_count << '\t' << d.teacher_count << '\t' << d.graduate_count << endl;
        }
    }
};

class Solution {
    Dataset ds;

   public:
    void case1() {
        ds.reset();
        ds.read();
        VERBOSE("Read function finished", endl);
        ds.printHeights();
    }
    void case2(int k = 1) {
        if (ds.isEmpty()) {
            cout << "\nPlease choose command 1 first!" << endl;
            return;
        }
        if (k == 1) {
            ds.queryByGraduateCount();
        } else if (k == 2) {
            ds.queryBySchoolName();
        } else {
            cout << "\nPlease choose command 1 first!" << endl;
            return;
        }
    }
};
void WriteMenu() {
    cout << "\n*** University Graduate Information System ***\n"
            "* 0. Quit                                    *\n"
            "* 1. Create Two Binary Search Trees          *\n"
            "* 2. Search by Number of Graduates           *\n"
            "* 3. Search by School Name                   *\n"
            "**********************************************"
         << endl;
    cout << "Input a command(0, 1-4): ";
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
        } else if (command == "2")
            sol.case2(1);
        else if (command == "3")
            sol.case2(2);
        else
            cout << "\nCommand does not Exist!!!" << endl;
        WriteMenu();
    }
    // cerr << "Time: " << (double)clock() / (double)CLOCKS_PER_SEC << '\n';
    return 0;
}
