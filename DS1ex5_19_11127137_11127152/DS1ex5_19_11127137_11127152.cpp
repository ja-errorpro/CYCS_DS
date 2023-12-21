// 11127137 ¶À¤A®a   11127152 ³¢©É·©

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <new>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

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
class BST {
   private:
    struct _TNode {
        int cmp_key;
        T data;
        _TNode *left, *right;
        _TNode(const int c, const T &d, _TNode *l = nullptr, _TNode *r = nullptr)
            : cmp_key(c), data(d), left(l), right(r) {}
    };
    _TNode *root;
    _TNode *min(_TNode *cur_ptr) { // find the minimum node
        if (cur_ptr == nullptr) return nullptr;
        while (cur_ptr->left != nullptr) cur_ptr = cur_ptr->left;
        return cur_ptr;
    }
    _TNode *max(_TNode *cur_ptr) { // find the maximum node
        if (cur_ptr == nullptr) return nullptr;
        while (cur_ptr->right != nullptr) cur_ptr = cur_ptr->right;
        return cur_ptr;
    }
    _TNode *insert(_TNode *root, const T &data, const int &cmp_key = 0) {
        _TNode **cur_ptr = &root;
        _TNode *new_node = nullptr;
        try {
            new_node = new _TNode(cmp_key, data);
        } catch (bad_alloc &e) {
            cout << "### Memory allocation failed! ###" << endl;
            return root;
        }
        while (*cur_ptr != nullptr) {
            if (cmp_key < (*cur_ptr)->cmp_key)
                cur_ptr = &((*cur_ptr)->left);
            else
                cur_ptr = &((*cur_ptr)->right);
        }
        *cur_ptr = new_node;
        return root;
    }

    _TNode *query(_TNode *cur_ptr, const int &cmp_key) {
        if (cur_ptr == nullptr) return nullptr;
        if (cmp_key == cur_ptr->cmp_key) return cur_ptr;
        if (cmp_key < cur_ptr->cmp_key)
            return query(cur_ptr->left, cmp_key);
        else
            return query(cur_ptr->right, cmp_key);
    }

    _TNode *erase(_TNode *cur_ptr, const int &cmp_key) {
        if (cur_ptr == nullptr) return nullptr;
        if (cmp_key < cur_ptr->cmp_key)
            cur_ptr->left = erase(cur_ptr->left, cmp_key);
        else if (cmp_key > cur_ptr->cmp_key)
            cur_ptr->right = erase(cur_ptr->right, cmp_key);
        else {
            if (cur_ptr->left == nullptr) { // no left child, replace with right child
                _TNode *tmp = cur_ptr->right;
                delete cur_ptr;
                return tmp;
            } else if (cur_ptr->right == nullptr) { // no right child, replace with left child
                _TNode *tmp = cur_ptr->left;
                delete cur_ptr;
                return tmp;
            }
            _TNode *tmp = min(cur_ptr->right); // find the minimum node in right subtree
            cur_ptr->cmp_key = tmp->cmp_key;
            cur_ptr->data = tmp->data;
            cur_ptr->right = erase(cur_ptr->right, tmp->cmp_key);
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

   public:
    BST() : root(nullptr) {}
    ~BST() {
        clear();

        VERBOSE("Destructor finished", endl);
    }
    void insert(const T &data, const int &cmp_key) {
        root = insert(root, data, cmp_key);
        // VERBOSE("Insert function finished", endl);
    }

    void erase(const T &data) { root = erase(root, data); }
    void clear() { root = clear(root); }
    bool empty() const { return root == nullptr; }
    vector<T> preOrder() { return preOrder(root); }
    vector<T> inOrder() { return inOrder(root); }
    vector<T> postOrder() { return postOrder(root); }
    int getHeight() { return getHeight(root); }

    vector<T> getInOrder() { return inOrder(root); }
    vector<T> getPreOrder() { return preOrder(root); }
    vector<T> getPostOrder() { return postOrder(root); }
    T queryLeftMost() { return min(root)->data; }
    T queryRightMost() { return max(root)->data; }
};

template <class T>
class MaxHeap {
    struct _HNode {
        int cmp_key;
        T data;
        _HNode(const int c, const T &d) : cmp_key(c), data(d) {}
    };
    vector<_HNode> _heap;
    int _size;
    void heapify(int i) {
        int l = (i << 1) | 1; // left child index
        int r = (i << 1) + 2; // right child index
        int largest = i;
        if (l < _size && _heap[l].cmp_key > _heap[largest].cmp_key) largest = l; // find the largest one
        if (r < _size && _heap[r].cmp_key > _heap[largest].cmp_key) largest = r;
        if (largest != i) {
            swap(_heap[i], _heap[largest]); // swap the largest one to the top
            heapify(largest);               // heapify the subtree
        }
    }
    void _build() {
        for (int i = (_size >> 1) - 1; i >= 0; i--) { // heapify from the last non-leaf node
            heapify(i);
        }
    }
    void _clear() {
        _heap.clear();
        _size = 0;
    }
    void _insert(const T &data, const int &cmp_key) { // insert a node to the heap
        _heap.push_back(_HNode(cmp_key, data));
        _size++;
        int i = _size - 1;
        while (i > 0 && _heap[i].cmp_key > _heap[(i - 1) >> 1].cmp_key) {
            // swap with parent if cmp_key is larger than parent
            swap(_heap[i], _heap[(i - 1) >> 1]);
            i = (i - 1) >> 1;
        }
    }
    void _pop() { // extract the top node (max)
        swap(_heap[0], _heap[_size - 1]);
        _size--;
        heapify(0);
    }
    int _getHeight() {
        int h = 0;
        int i = _size - 1;
        while (i > 0) {
            h++;
            i = (i - 1) >> 1;
        }
        return h;
    }
    T _getLeftMost(int &index) {
        int i = 0;
        while ((i << 1) + 1 < _size) i = (i << 1) + 1;
        index = i;
        return _heap[i].data;
    }
    T _getRightMost(int &index) {
        index = _size - 1;
        return _heap[index].data;
    }

   public:
    MaxHeap() : _size(0) {}
    ~MaxHeap() { _clear(); }
    void clear() { _clear(); }
    bool empty() const { return _size == 0; }
    void setHeap(const vector<T> &arr, const vector<int> &cmp_key_arr) {
        _clear();
        for (int i = 0; i < arr.size(); i++) {
            _heap.push_back(_HNode(cmp_key_arr[i], arr[i]));
        }
        _size = arr.size();
        _build();
    }
    void insert(const T &data, const int &cmp_key) { _insert(data, cmp_key); }
    void pop() { _pop(); }
    T top() { return _heap[0].data; }
    int size() const { return _size; }
    int getHeight() { return _getHeight(); }
    T getLeftMost(int &index) { return _getLeftMost(index); }
    T getRightMost(int &index) { return _getRightMost(index); }
    vector<T> getHeap() {
        vector<T> ans;
        for (auto &node : _heap) {
            ans.push_back(node.data);
        }
        return ans;
    }
};

class Data {
    struct _data {
        int id;
        string pokemon_name;
        string type1;
        int hp;
        int attack;
        int defense;
    };
    vector<_data> _data_arr;
    unordered_map<int, _data> _data_hash_table;

    BST<int> _bst_by_hp; // BST stores the id of pokemon, sorted by hp
    MaxHeap<int> _maxheap_by_hp;
    string _filename;
    void _insertBST(int index, const _data &data) { _bst_by_hp.insert(index, data.hp); }
    void _insertMaxHeap(int index, const _data &data) { _maxheap_by_hp.insert(index, data.hp); }
    void _clear() {
        _data_arr.clear();
        _data_hash_table.clear();
        _bst_by_hp.clear();
        _maxheap_by_hp.clear();
    }

   public:
    Data() {}
    ~Data() { _clear(); }
    void reset() {
        _clear();
        _filename.clear();
    }

    bool isEmpty() const { return _data_arr.empty(); }
    /*
        Read data from file
        @return: 1 for success, 0 for quit, -1 for fail
        @side effect: update _data_arr, _data_hash_table, _bst_by_hp, _maxheap_by_hp, _filename
    */
    int read() {
        if (_filename.empty()) {
            cout << "\nInput a file number [0: quit]: ";
            cin >> _filename;
            cin.ignore();
            if (_filename == "0") return 0;
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
        getline(fin, tmp); // skip the first line

        int i = 0;
        while (getline(fin, tmp)) {
            stringstream ss(tmp);
            _data data;
            vector<string> read_line_data_tmp;
            string line_tmp;
            while (getline(ss, line_tmp, '\t')) read_line_data_tmp.push_back(line_tmp); // split by tab
            data.id = stoi(read_line_data_tmp.at(0));
            data.pokemon_name = read_line_data_tmp.at(1);
            data.type1 = read_line_data_tmp.at(2);
            data.hp = stoi(read_line_data_tmp.at(5));
            data.attack = stoi(read_line_data_tmp.at(6));
            data.defense = stoi(read_line_data_tmp.at(7));
            _data_arr.push_back(data);
            _data_hash_table[i] = data;
            _insertBST(i++, data);
        }

        if (_data_arr.empty()) {
            cout << "\n### Get nothing from the file " << _filename << " ! ###" << endl;
            _filename.clear();
            return 0;
        }
        fin.close();
        return 1;
    }
    /*
        Build Max Heap from _data_arr by hp
        @side effect: update _maxheap_by_hp
    */
    void BuildMaxHeap() {
        if (_data_arr.empty()) {
            cout << "\nThere is no data!" << endl;
            return;
        }
        vector<int> cmp_key_arr;
        for (auto &data : _data_arr) {
            cmp_key_arr.push_back(data.hp);
        }
        vector<int> arr;
        for (int i = 0; i < _data_arr.size(); i++) {
            arr.push_back(i);
        }
        _maxheap_by_hp.setHeap(arr, cmp_key_arr);
    }
    /*
        Print the height of BST
    */
    void printBSTHeight() {
        if (_bst_by_hp.empty()) {
            cout << "\nThere is no data!" << endl;
            return;
        }
        cout << "HP tree height = " << _bst_by_hp.getHeight() << endl;
    }
    /*
        Print the height of Max Heap
    */
    void printHeapHeight() {
        if (_maxheap_by_hp.empty()) {
            cout << "\nThere is no data!" << endl;
            return;
        }
        cout << "HP heap height = " << _maxheap_by_hp.getHeight() + 1 << endl;
    }
    /*
        Print the data by index
        @param index: the index of data
        @param w: the width of output
        @param offset: the offset of index
    */
    void printByIndex(int index, int w = 2, int offset = 0) {
        if (_data_arr.empty()) {
            cout << "\nThere is no data!" << endl;
            return;
        }

        cout << "[" << setw(w) << right << index + offset << "]\t" << left;
        cout << _data_arr[index].id << '\t' << setw(24) << _data_arr[index].pokemon_name << '\t' << setw(10)
             << _data_arr[index].type1 << '\t' << setw(6) << _data_arr[index].hp << '\t'
             << _data_arr[index].attack << '\t' << _data_arr[index].defense << endl;
    }
    /*
        Print the data by hash key
        @param index: the hash key of data
        @param w: the width of output
        @param offset: the offset of index
    */
    void printByHashKey(int index, int w = 2, int offset = 0) {
        if (_data_arr.empty()) {
            cout << "\nThere is no data!" << endl;
            return;
        }
        if (_data_hash_table.find(index) == _data_hash_table.end()) {
            return;
        }

        cout << "[" << setw(w) << right << index + offset << "]\t" << left;
        cout << _data_hash_table[index].id << '\t' << setw(24) << _data_hash_table[index].pokemon_name << '\t'
             << setw(10) << _data_hash_table[index].type1 << '\t' << setw(6) << _data_hash_table[index].hp
             << '\t' << _data_hash_table[index].attack << '\t' << _data_hash_table[index].defense << endl;
    }
    /*
        Print all data in array
    */
    void printByArray() {
        if (_data_arr.empty()) {
            cout << "\nThere is no data!" << endl;
            return;
        }
        cout << "\t#\tName                    \tType 1    \tHP\tAttack\tDefense" << endl;
        int n = _data_arr.size(); // n = _data_hash_table.size();
        for (int i = 0; i < n; i++) {
            printByIndex(i, 2, 1);
        }
    }
    /*
        print the leftmost node in BST
    */
    void printBSTLeftMost() {
        int index = _bst_by_hp.queryLeftMost();
        cout << "Leftmost node: " << endl;
        cout << "\t#\tName                    \tType 1    \tHP\tAttack\tDefense" << endl;
        printByIndex(index, 3, 1);
    }
    /*
        print the rightmost node in BST
    */
    void printBSTRightMost() {
        int index = _bst_by_hp.queryRightMost();
        cout << "Rightmost node: " << endl;
        cout << "\t#\tName                    \tType 1    \tHP\tAttack\tDefense" << endl;
        printByIndex(index, 3, 1);
    }
    /*
        print the leftmost node in Max Heap
    */
    void printHeapLeftMost() {
        int heap_index = 0;
        int index = _maxheap_by_hp.getLeftMost(heap_index);
        cout << "Leftmost node: " << endl;
        cout << "\t#\tName                    \tType 1    \tHP\tAttack\tDefense" << endl;
        cout << "[" << right << heap_index << "]\t" << left;
        cout << _data_arr[index].id << '\t' << setw(24) << _data_arr[index].pokemon_name << '\t' << setw(10)
             << _data_arr[index].type1 << '\t' << setw(6) << _data_arr[index].hp << '\t'
             << _data_arr[index].attack << '\t' << _data_arr[index].defense << endl;
    }
    /*
        print the rightmost node in Max Heap
    */
    void printHeapRightMost() {
        int heap_index = 0;
        int index = _maxheap_by_hp.getRightMost(heap_index);
        cout << "Bottom: " << endl;
        cout << "\t#\tName                    \tType 1    \tHP\tAttack\tDefense" << endl;
        cout << "[" << right << heap_index << "]\t" << left;
        cout << _data_arr[index].id << '\t' << setw(24) << _data_arr[index].pokemon_name << '\t' << setw(10)
             << _data_arr[index].type1 << '\t' << setw(6) << _data_arr[index].hp << '\t'
             << _data_arr[index].attack << '\t' << _data_arr[index].defense << endl;
    }
    /*
        print the Max Heap
    */
    void printHeap() {
        if (_maxheap_by_hp.empty()) {
            cout << "\nThere is no data!" << endl;
            return;
        }
        cout << "\t#\tName                    \tType 1    \tHP\tAttack\tDefense" << endl;
        int n = _maxheap_by_hp.size();
        vector<int> heap = _maxheap_by_hp.getHeap();
        for (int i = 0; i < n; i++) {
            int index = heap[i];
            cout << "[" << setw(2) << right << i << "]\t" << left;
            cout << _data_hash_table[index].id << '\t' << setw(24) << _data_hash_table[index].pokemon_name
                 << '\t' << setw(10) << _data_hash_table[index].type1 << '\t' << setw(6)
                 << _data_hash_table[index].hp << '\t' << _data_hash_table[index].attack << '\t'
                 << _data_hash_table[index].defense << endl;
        }
    }
};

class Solution {
    Data _ds;

   public:
    void case1() {
        _ds.reset();
        int state = _ds.read();
        while (state == -1) state = _ds.read();
        if (state == 1) {
            _ds.printByArray();
            _ds.printBSTHeight();
            _ds.printBSTLeftMost();
            _ds.printBSTRightMost();
        }
    }
    void case2() {
        if (_ds.isEmpty()) {
            cout << "\n----- Execute Mission 1 first! -----" << endl;
            return;
        }
        _ds.BuildMaxHeap();
        _ds.printHeap();
        _ds.printHeapHeight();
        _ds.printHeapLeftMost();
        _ds.printHeapRightMost();
    }
};

void WriteMenu() {
    cout << "\n***** Pokemon Tree and Heap *****\n"
            "* 0. QUIT                       *\n"
            "* 1. Read a file to build BST   *\n"
            "* 2. Transform it into Max Heap *\n"
            "*********************************\n"
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
        } else
            cout << "\nCommand does not Exist!!!" << endl;
        WriteMenu();
    }
    // cerr << "Time: " << (double)clock() / (double)CLOCKS_PER_SEC << '\n';
    return 0;
}
