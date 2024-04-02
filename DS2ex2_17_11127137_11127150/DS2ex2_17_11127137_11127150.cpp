// 11127137 ¶À¤A®a, 11127150 ±iºÍ®¦
/****************************************************/
/*  CPP Template for School                         */
/*  Author: CompileErr0r(YiJia)                     */
/*  Author ID: 11127137                             */
/*  Compile Environment: Linux 5.15.90.1 WSL x86_64 */
/*  Compiler: g++ 9.4                               */
/****************************************************/

#include <algorithm>
#include <cassert>
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
struct slotData {
    vector<T> data;
    int key;
};

template <class T>
class two3Tree {
    struct Node {
        vector<slotData<T>> data; // pair<data, key>
        vector<Node *> children;
        Node *parent;
        Node() : parent(nullptr) {}
        Node(T data) : data(data), parent(nullptr) {}

        /*
            Insert data into current node.
            If the key is already in the node, merge the data.
            @param insert_data: the data to be inserted
        */
        void insertCurrentNode(slotData<T> insert_data) {
            data.push_back(insert_data);
            sort(data.begin(), data.end(), [](slotData<T> a, slotData<T> b) { return a.key < b.key; });
            // merge
            for (int i = 0; i < (int)data.size() - 1; i++) {
                if (data[i].key == data[i + 1].key) {
                    data[i].data.insert(data[i].data.end(), data[i + 1].data.begin(), data[i + 1].data.end());
                    data.erase(data.begin() + i + 1);
                }
            }
        }

        /*
            Insert child node into current node.
            Sort the children by key.
            If the key of two children are the same, merge the data.
            @param child: the child node to be inserted
        */
        void insertChildNode(Node *child) {
            children.push_back(child);
            sort(children.begin(), children.end(),
                 [](Node *a, Node *b) { return a->data[0].key < b->data[0].key; });

            for (int i = 0; i < (int)children.size() - 1; i++) {
                if (children[i]->data[0].key == children[i + 1]->data[0].key) {
                    children[i]->data.insert(children[i]->data.end(), children[i + 1]->data.begin(),
                                             children[i + 1]->data.end());
                    children.erase(children.begin() + i + 1);
                }
            }
        }

        /*
            Pop the data with the key from the current node.
            @param pop_data: the key to be popped
        */
        void popCurrentNode(int pop_data) {
            for (int i = 0; i < (int)data.size(); i++) {
                if (data[i].key == pop_data) {
                    data.erase(data.begin() + i);
                    break;
                }
            }
        }

        /*
            Pop the child node from the current node.
            @param child: the child node to be popped
        */
        void popChildNode(Node *child) {
            for (int i = 0; i < (int)children.size(); i++) {
                if (children[i] == child) {
                    children.erase(children.begin() + i);
                    break;
                }
            }
        }

        /*
            Pull up the middle key to the parent node.
            If the parent node is nullptr, create a new parent node.
        */
        void pullUp() {
            Node *left = new Node();
            Node *right = new Node();
            left->data.push_back(data[0]);
            right->data.push_back(data[2]);
            if (!children.empty()) {
                left->insertChildNode(children[0]);
                left->insertChildNode(children[1]);
                right->insertChildNode(children[2]);
                right->insertChildNode(children[3]);
                children[0]->parent = left;
                children[1]->parent = left;
                children[2]->parent = right;
                children[3]->parent = right;
            }

            if (parent == nullptr) {
                parent = new Node();
                parent->insertChildNode(this);
            }
            parent->insertCurrentNode(data[1]);
            parent->popChildNode(this);
            parent->insertChildNode(left);
            parent->insertChildNode(right);
            left->parent = parent;
            right->parent = parent;
        }
    };

    Node *root;

    /*
        Clear the tree.
        @param node: the node to be cleared
    */
    void _clear(Node *&node) {
        if (node == nullptr) return;
        for (Node *child : node->children) _clear(child);
        delete node;
        node = nullptr;
    }

    /*
        Insert data into the tree.
        If the key is already in the tree, merge the data.
        @param data: the data to be inserted
        @param node: the node to be inserted
    */
    void _insert(slotData<T> data, Node *node) {
        for (int i = 0; i < (int)node->data.size(); i++) {
            if (data.key == node->data[i].key) {
                node->data[i].data.insert(node->data[i].data.end(), data.data.begin(), data.data.end());
                return;
            }
        }
        if (node->children.empty()) {
            node->insertCurrentNode(data);
            while (node != nullptr && (int)node->data.size() == 3) {
                node->pullUp();
                Node *tmp = node;
                node = node->parent;
                delete tmp;
            }
            if (node->parent == nullptr) root = node;
            return;
        }
        for (int i = 0; i < (int)node->data.size(); i++) {
            if (data.key < node->data[i].key) {
                _insert(data, node->children[i]);
                return;
            }
        }
        _insert(data, node->children.back());
    }

    int _getHeight(Node *node) {
        if (node == nullptr) return 0;
        int height = 1;
        for (Node *child : node->children) height = max(height, _getHeight(child) + 1);
        return height;
    }

    int _size(Node *node) { // count of nodes
        if (node == nullptr) return 0;
        int size = 1;
        for (Node *child : node->children) size += _size(child);
        return size;
    }

    int _dataSize(Node *node) { // count of data
        if (node == nullptr) return 0;
        int size = 0;
        for (slotData<T> data : node->data) size += data.data.size();
        for (Node *child : node->children) size += _dataSize(child);
        return size;
    }

    /*
        Query the data with the key from the tree.
        @param key: the key to be queried
        @param node: the node to be queried
        @return: the node with the key, nullptr if not found
    */
    Node *_query(int key, Node *node) {
        if (node == nullptr) return nullptr;
        for (int i = 0; i < (int)node->data.size(); i++) {
            if (key == node->data[i].key) return node;
        }
        if (node->children.empty()) return nullptr;
        for (int i = 0; i < (int)node->data.size(); i++) {
            if (key < node->data[i].key) return _query(key, node->children[i]);
        }
        return _query(key, node->children.back());
    }

    void _getTopKMax(Node *node, int k, vector<T> &res) {
        if (res.size() >= k) return;
        if (node == nullptr) return;
        if (node->children.empty()) {
            for (int i = (int)node->data.size() - 1; i >= 0; i--) {
                if ((int)res.size() >= k) return;
                for (int j = 0; j < node->data[i].data.size(); j++) {
                    res.push_back(node->data[i].data[j]);
                }
            }
            return;
        }

        for (int i = (int)node->children.size() - 1; i >= 0; i--) {
            _getTopKMax(node->children[i], k, res);
            if ((int)res.size() >= k) return;
            if (i - 1 >= 0 && !node->data[i - 1].data.empty()) {
                for (int j = 0; j < node->data[i - 1].data.size(); j++) {
                    res.push_back(node->data[i - 1].data[j]);
                }
            }
        }
    }

   public:
    two3Tree() : root(nullptr) {}
    ~two3Tree() { _clear(root); }
    void insert(int key, T data) {
        slotData<T> insert_data;
        insert_data.key = key;
        insert_data.data.push_back(data);
        if (root == nullptr) {
            root = new Node();
            root->insertCurrentNode(insert_data);
            return;
        }
        _insert(insert_data, root);
    }

    int getHeight() { return _getHeight(root); }
    int size() { return _size(root); }
    int dataSize() { return _dataSize(root); }
    void clear() { _clear(root); }

    vector<T> queryTopKMax(int k) {
        vector<T> res;
        _getTopKMax(root, k, res);
        return res;
    }

    vector<T> query(int key) {
        Node *node = _query(key, root);
        if (node == nullptr) return {};
        for (slotData<T> data : node->data) {
            if (data.key == key) return data.data;
        }
        return {};
    }

    vector<T> queryRoot() {
        vector<T> res;
        for (slotData<T> data : root->data) {
            res.insert(res.end(), data.data.begin(), data.data.end());
        }
        return res;
    }
};

template <class T>
class AVL {
    struct Node {
        slotData<T> data;
        Node *left;
        Node *right;
        Node *parent;
        int height;
        Node() : left(nullptr), right(nullptr), parent(nullptr), height(1) {}
        Node(slotData<T> data) : data(data), left(nullptr), right(nullptr), parent(nullptr), height(1) {}

        void update() {
            Node *left = this->left;
            Node *right = this->right;
            if (left == nullptr && right == nullptr) {
                height = 1;
            } else if (left == nullptr) {
                height = right->height + 1;
            } else if (right == nullptr) {
                height = left->height + 1;
            } else {
                height = max(left->height, right->height) + 1;
            }
        }
        int BalancedFactor() {
            Node *left = this->left;
            Node *right = this->right;
            if (left == nullptr && right == nullptr) return 0;
            if (left == nullptr) return -right->height;
            if (right == nullptr) return left->height;
            return left->height - right->height;
        }

        Node *rotateLeft() {
            Node *new_root = right;
            right = new_root->left;
            new_root->left = this;
            update();
            new_root->update();
            return new_root;
        }

        Node *rotateRight() {
            Node *new_root = left;
            left = new_root->right;
            new_root->right = this;
            update();
            new_root->update();
            return new_root;
        }

        int _getHeight(Node *node) {
            if (node == nullptr) return 0;
            int left_height = _getHeight(node->left);
            int right_height = _getHeight(node->right);
            return max(left_height, right_height) + 1;
        }
    };
    Node *root;

    void _clear(Node *&node) {
        if (node == nullptr) return;
        _clear(node->left);
        _clear(node->right);
        delete node;
        node = nullptr;
    }

    void _balance(Node *&node) {
        node->update();
        if (node->BalancedFactor() == 2) {
            if (node->left->BalancedFactor() < 0) node->left = node->left->rotateLeft();
            node = node->rotateRight();
        } else if (node->BalancedFactor() == -2) {
            if (node->right->BalancedFactor() > 0) node->right = node->right->rotateRight();
            node = node->rotateLeft();
        }
    }

    void _insert(slotData<T> data, Node *&node) {
        if (node == nullptr) {
            node = new Node(data);
            return;
        }
        if (data.key == node->data.key) {
            node->data.data.insert(node->data.data.end(), data.data.begin(), data.data.end());
            return;
        }
        if (data.key < node->data.key) {
            _insert(data, node->left);
        } else {
            _insert(data, node->right);
        }
        _balance(node);
    }

    int _getHeight(Node *node) {
        if (node == nullptr) return 0;
        return node->height;
    }

    int _size(Node *node) { // count of nodes
        if (node == nullptr) return 0;
        return 1 + _size(node->left) + _size(node->right);
    }

    int _DataSize(Node *node) { // count of data
        if (node == nullptr) return 0;
        return node->data.data.size() + _DataSize(node->left) + _DataSize(node->right);
    }

    Node *_query(int key, Node *node) {
        if (node == nullptr) return nullptr;
        if (key == node->data.key) return node;
        if (key < node->data.key) return _query(key, node->left);
        return _query(key, node->right);
    }

    void _getTopKMax(Node *node, int k, vector<T> &res) {
        if (node == nullptr) return;
        _getTopKMax(node->right, k, res);
        if ((int)res.size() < k) {
            res.insert(res.end(), node->data.data.begin(), node->data.data.end());
        }
        if ((int)res.size() >= k) return;
        _getTopKMax(node->left, k, res);
    }

   public:
    AVL() : root(nullptr) {}
    ~AVL() { _clear(root); }
    void insert(int key, T data) {
        slotData<T> insert_data;
        insert_data.key = key;
        insert_data.data.push_back(data);
        if (root == nullptr) {
            root = new Node(insert_data);
            return;
        }
        _insert(insert_data, root);
    }

    int getHeight() { return _getHeight(root); }
    int size() { return _size(root); }
    int dataSize() { return _DataSize(root); }
    void clear() { _clear(root); }

    vector<T> query(int key) {
        Node *node = _query(key, root);
        if (node == nullptr) return {};
        return node->data.data;
    }

    vector<T> queryRoot() { return root->data.data; }
    vector<T> queryTopKMax(int k) {
        vector<T> res;
        _getTopKMax(root, k, res);
        return res;
    }
};

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

    two3Tree<int> _btree_by_graduate;
    AVL<int> _avl_by_student;

    string _filename;

    void _clear() {
        _data_arr.clear();
        _btree_by_graduate.clear();
        _avl_by_student.clear();
    }

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

    bool isEmpty() { return _data_arr.empty(); }
    bool isAVLEmpty() { return _avl_by_student.size() == 0; }
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

    void build23Tree() {
        for (int i = 0; i < (int)_data_arr.size(); i++) {
            _btree_by_graduate.insert(_data_arr[i].graduate_count, i);
        }
        //_btree_by_graduate.test_printAll();
    }

    void buildAVL() {
        for (int i = 0; i < (int)_data_arr.size(); i++) {
            _avl_by_student.insert(_data_arr[i].student_count, i);
        }
    }

    void print23TreeInfo() {
        cout << "Tree height = " << _btree_by_graduate.getHeight() << endl;
        cout << "Number of nodes = " << _btree_by_graduate.size() << endl;

        vector<int> root_data = _btree_by_graduate.queryRoot();
        for (int i = 0; i < (int)root_data.size(); i++) {
            cout << i + 1 << ": [" << root_data[i] + 1 << "] " << _data_arr[root_data[i]].school_name << ", "
                 << _data_arr[root_data[i]].department_name << ", " << _data_arr[root_data[i]].day_further
                 << ", " << _data_arr[root_data[i]].level << ", " << _data_arr[root_data[i]].student_count
                 << ", " << _data_arr[root_data[i]].graduate_count << endl;
        }
        cout << endl;
    }

    void printAVLTreeInfo() {
        cout << "Tree height = " << _avl_by_student.getHeight() << endl;
        cout << "Number of nodes = " << _avl_by_student.size() << endl;

        vector<int> root_data = _avl_by_student.queryRoot();
        for (int i = 0; i < (int)root_data.size(); i++) {
            cout << i + 1 << ": [" << root_data[i] + 1 << "] " << _data_arr[root_data[i]].school_name << ", "
                 << _data_arr[root_data[i]].department_name << ", " << _data_arr[root_data[i]].day_further
                 << ", " << _data_arr[root_data[i]].level << ", " << _data_arr[root_data[i]].student_count
                 << ", " << _data_arr[root_data[i]].graduate_count << endl;
        }
        cout << endl;
    }

    void print23TreeTopKMax() {
        int k;
        int btreeSize = _btree_by_graduate.dataSize();
        cout << "\nEnter K in [1, " << btreeSize << "]: ";
        cin >> k;
        if (k < 1 || k > btreeSize) {
            return;
        }
        vector<int> topKMax = _btree_by_graduate.queryTopKMax(k);
        assert(topKMax.size() == k);
        for (int i = 0; i < k; i++) {
            cout << i + 1 << ": [" << topKMax[i] + 1 << "] " << _data_arr[topKMax[i]].school_name << ", "
                 << _data_arr[topKMax[i]].department_name << ", " << _data_arr[topKMax[i]].day_further << ", "
                 << _data_arr[topKMax[i]].level << ", " << _data_arr[topKMax[i]].student_count << ", "
                 << _data_arr[topKMax[i]].graduate_count << endl;
        }
        cout << endl;
    }

    void printAVLTopKMax() {
        int k;
        int avlSize = _avl_by_student.dataSize();
        cout << "\nEnter K in [1, " << avlSize << "]: ";
        cin >> k;
        if (k < 1 || k > avlSize) {
            return;
        }
        vector<int> topKMax = _avl_by_student.queryTopKMax(k);
        for (int i = 0; i < k; i++) {
            cout << i + 1 << ": [" << topKMax[i] + 1 << "] " << _data_arr[topKMax[i]].school_name << ", "
                 << _data_arr[topKMax[i]].department_name << ", " << _data_arr[topKMax[i]].day_further << ", "
                 << _data_arr[topKMax[i]].level << ", " << _data_arr[topKMax[i]].student_count << ", "
                 << _data_arr[topKMax[i]].graduate_count << endl;
        }
        cout << endl;
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
            _ds.build23Tree();
            _ds.print23TreeInfo();
        }
    }
    void case2() {
        if (_ds.isEmpty()) {
            cout << "### Choose 1 first. ###" << endl;
            return;
        }
        if (_ds.isAVLEmpty()) {
            _ds.buildAVL();
        } else {
            cout << "### AVL tree has been built. ###\n";
        }
        _ds.printAVLTreeInfo();
    }

    void case3() {
        if (_ds.isEmpty()) {
            cout << "### Choose 1 first. ###" << endl;
            return;
        }
        _ds.print23TreeTopKMax();
    }

    void case4() {
        if (_ds.isEmpty()) {
            cout << "### Choose 1 first. ###" << endl;
            return;
        }
        if (_ds.isAVLEmpty()) {
            cout << "### Choose 2 first. ###" << endl;
            return;
        }
        _ds.printAVLTopKMax();
    }
};

void WriteMenu() {
    cout << "\n**** Balanced Search Trees ****\n"
            "* 0. QUIT                     *\n"
            "* 1. Build 23 tree            *\n"
            "* 2. Build AVL tree           *\n"
            "* 3. Top-K search on 23 tree  *\n"
            "* 4. Top-K search on AVL tree *\n"
            "*******************************\n"
            "Input a choice(0, 1, 2, 3, 4): ";
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

        else if (command == "3")
            sol.case3();

        else if (command == "4")
            sol.case4();
#ifdef CompileErr0rDEBUGGING
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
