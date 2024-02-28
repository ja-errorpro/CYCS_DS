// 11127137 ���A�a

#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <new>
#include <numeric>
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
        _heap.pop_back();
        _size--;
        heapify(0);
    }
    void _pop(T &data) { // extract the top node (max)
        data = _heap[0].data;
        swap(_heap[0], _heap[_size - 1]);
        _heap.pop_back();
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
    void pop(T &data) { _pop(data); }
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
}; // class MaxHeap

template <class T>
class MinHeap {
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
        int smallest = i;
        if (l < _size && _heap[l].cmp_key < _heap[smallest].cmp_key) smallest = l; // find the smallest one
        if (r < _size && _heap[r].cmp_key < _heap[smallest].cmp_key) smallest = r;
        if (smallest != i) {
            swap(_heap[i], _heap[smallest]); // swap the largest one to the top
            heapify(smallest);               // heapify the subtree
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
        while (i > 0 && _heap[i].cmp_key < _heap[(i - 1) >> 1].cmp_key) {
            // swap with parent if cmp_key is less than parent
            swap(_heap[i], _heap[(i - 1) >> 1]);
            i = (i - 1) >> 1;
        }
    }
    void _pop() { // extract the top node (max)
        swap(_heap[0], _heap[_size - 1]);
        _heap.pop_back();
        _size--;
        heapify(0);
    }
    void _pop(T &data) { // extract the top node (max)
        data = _heap[0].data;
        swap(_heap[0], _heap[_size - 1]);
        _heap.pop_back();
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
    MinHeap() : _size(0) {}
    ~MinHeap() { _clear(); }
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
    void pop(T &data) { _pop(data); }
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
}; // class MinHeap

template <class T>
class Deap {
    struct _DNode {
        int cmp_key;
        T data;
        _DNode(const int c, const T &d) : cmp_key(c), data(d) {}
    };

    vector<_DNode> _deap;
    int _size;

    int _getHeight() { return floor(log2(_size + 1)); }
    int _getLevel(int index) {
        return floor(log2(index + 1)) + 1; // let root level = 1, index is 0-based
    }
    int _getParent(int index) { return (index - 1) >> 1; }
    int _getLeftChild(int index) { return (index << 1) + 1; }
    int _getRightChild(int index) { return (index << 1) + 2; }

    T _getLeftMost(int &index) {
        int i = 1;
        while ((i << 1) + 1 < _size) i = (i << 1) + 1;
        index = i;
        return _deap[i].data;
    }

    T _getRightMost(int &index) {
        index = _size - 1;
        return _deap[index].data;
    }

    int _getMinHeapCorrespondingToMaxHeapIndex(int index) {
        if (index < 0) {
            throw "Invalid index";
        }
        if (index == 0) return 0; // root
        int ans = index + (1 << (_getLevel(index) - 2));
        if (ans >= _size)
            ans = _getParent(ans); // if cannot find the corresponding min heap, choose the parent node
        return ans;
    }

    int _getMaxHeapCorrespondingToMinHeapIndex(int index) {
        if (index < 0) {
            throw "Invalid index";
        }
        if (index == 0) return 0; // root
        int ans = index - (1 << (_getLevel(index) - 2));
        return ans;
    }

    bool _atMinHeap(int index) {
        int minRoot = 1;

        int parent = _getParent(index);
        while (parent > 0) {
            index = parent;
            parent = _getParent(parent);
        }

        return index == minRoot;
    }
    int _getCorrespondingIndex(int index) {
        if (_atMinHeap(index)) {
            return _getMinHeapCorrespondingToMaxHeapIndex(index);
        } else {
            return _getMaxHeapCorrespondingToMinHeapIndex(index);
        }
    }
    void _minHeapify(int index) { // bottom up
        int parent = _getParent(index);
        while (index > 2 && _deap.at(index).cmp_key < _deap.at(parent).cmp_key) {
            swap(_deap[index], _deap[parent]);
            index = parent;
            parent = _getParent(index);
        }
    }

    void _maxHeapify(int index) { // bottom up
        int parent = _getParent(index);
        while (index > 2 && _deap.at(index).cmp_key > _deap.at(parent).cmp_key) {
            swap(_deap[index], _deap[parent]);
            index = parent;
            parent = _getParent(index);
        }
    }

    void _deapify() {
        if (_size <= 2) return;
        int correspondIndex = _getCorrespondingIndex(_size - 1);
        if (_atMinHeap(_size - 1)) {
            if (_deap.at(_size - 1).cmp_key > _deap.at(correspondIndex).cmp_key) {
                swap(_deap[_size - 1], _deap[correspondIndex]);
                _maxHeapify(correspondIndex);
            } else {
                _minHeapify(_size - 1);
            }
        } else {
            if (_deap[_size - 1].cmp_key < _deap[correspondIndex].cmp_key) {
                swap(_deap[_size - 1], _deap[correspondIndex]);
                _minHeapify(correspondIndex);
            } else {
                _maxHeapify(_size - 1);
            }
        }
    }

    void _deapify(int index) {
        if (index <= 2) return;
        int correspondIndex = _getCorrespondingIndex(index);
        if (_atMinHeap(index)) {
            if (_deap.at(index).cmp_key > _deap.at(correspondIndex).cmp_key) {
                swap(_deap[index], _deap[correspondIndex]);
                _maxHeapify(correspondIndex);
            } else {
                _minHeapify(index);
            }
        } else {
            if (_deap[index].cmp_key < _deap[correspondIndex].cmp_key) {
                swap(_deap[index], _deap[correspondIndex]);
                _minHeapify(correspondIndex);
            } else {
                _maxHeapify(index);
            }
        }
    }

    void _insert(const T &data, const int &cmp_key) {
        _deap.push_back(_DNode(cmp_key, data));
        _size++;
        _deapify();
    }

    void _insert(const T &data, const int &cmp_key, int index) {
        if (index == _size) {
            _insert(data, cmp_key);
            return;
        }
        _deap[index] = _DNode(cmp_key, data);
        _deapify(index);
    }

    void _clear() {
        _deap.clear();
        _deap.push_back(_DNode(INT_MIN, T())); // dummy node
        _size = 1;
    }

    T _pop_min() {
        if (_size == 1) return T();

        _DNode pop_element = _deap[1];
        _DNode last_element = _deap[_size - 1];
        if (_size <= 3) { // only one or two elements
            _deap[1] = _deap[_size - 1];
            _deap.pop_back();
            _size--;
            return pop_element.data;
        }
        _deap.pop_back(); // delete the last element
        _size--;

        int index = 1;
        while (_getLeftChild(index) < _size) { // move each smaller node up
            int left = _getLeftChild(index);
            int right = _getRightChild(index);
            int smaller = (right < _size && _deap[right].cmp_key < _deap[left].cmp_key) ? right : left;

            if (smaller < _size) {
                _deap[index] = _deap[smaller];
                index = smaller;
            }
        }

        _insert(last_element.data, last_element.cmp_key, index);

        return pop_element.data;
    }

    T _pop_max() {
        if (_size == 1) return T();

        _DNode pop_element = _deap[(_size == 2 ? 1 : 2)];
        _DNode last_element = _deap[_size - 1];

        _deap.pop_back();
        _size--;
        if (_size == 2) { // only two elements
            return pop_element.data;
        }
        int index = 2;
        while (_getLeftChild(index) < _size) {
            int left = _getLeftChild(index);
            int right = _getRightChild(index);
            int larger = (right < _size && _deap[right].cmp_key > _deap[left].cmp_key) ? right : left;

            if (larger < _size) {
                _deap[index] = _deap[larger];
                index = larger;
            }
        }

        _insert(last_element.data, last_element.cmp_key, index);

        return pop_element.data;
    }

   public:
    Deap() : _size(1) {
        _deap.push_back(_DNode(INT_MIN, T())); // dummy node
    }
    ~Deap() { _clear(); }
    void clear() { _clear(); }
    bool empty() const { return _size == 1; }
    void insert(const T &data, const int &cmp_key) { _insert(data, cmp_key); }
    T top() { return _deap[0].data; }
    int size() const { return _size; }
    T getLeftMost(int &index) { return _getLeftMost(index); }
    T getRightMost(int &index) { return _getRightMost(index); }
    vector<T> getDeap() {
        vector<T> ans;
        for (int i = 1; i < _size; i++) {
            ans.push_back(_deap[i].cmp_key);
        }
        return ans;
    }

    T pop_min() { return _pop_min(); }
    T pop_max() { return _pop_max(); }

}; // class Deap

template <class T>
class MinMaxHeap {
    struct _HNode {
        int cmp_key;
        T data;
        _HNode(const int c, const T &d) : cmp_key(c), data(d) {}
    };
    vector<_HNode> _heap;
    int _size;
    int _getHeight() { return floor(log2(_size + 1)); }
    int _getLevel(int index) { return floor(log2(index + 1)) + 1; }
    int _getParent(int index) { return (index - 1) >> 1; }
    int _getGrandParent(int index) { return _getParent(_getParent(index)); }
    int _getLeftChild(int index) { return (index << 1) + 1; }
    int _getRightChild(int index) { return (index << 1) + 2; }

    int _getLeftMost(int &index) {
        int i = 0;
        while ((i << 1) + 1 < _size) i = (i << 1) + 1;
        index = i;
        return _heap[i].data;
    }
    int _getRightMost(int &index) {
        index = _size - 1;
        return _heap[index].data;
    }
    bool _atMinLevel(int index) { return _getLevel(index) % 2; }
    bool _atMaxLevel(int index) { return !(_getLevel(index) % 2); }

    void _minHeapify(int index) { // only heapify the min level
        int grandParent = _getGrandParent(index);
        while (index > 2 && _heap.at(index).cmp_key < _heap.at(grandParent).cmp_key) {
            swap(_heap[index], _heap[grandParent]);
            index = grandParent;

            grandParent = _getGrandParent(index);
        }
    }

    void _maxHeapify(int index) { // only heapify the max level
        int grandParent = _getGrandParent(index);
        while (index > 2 && _heap.at(index).cmp_key > _heap.at(grandParent).cmp_key) {
            swap(_heap[index], _heap[grandParent]);
            index = grandParent;
            grandParent = _getGrandParent(index);
        }
    }

    void _minMaxHeapify(int index) {
        if (_size <= 2) return;
        int parent = _getParent(index);
        if (_atMinLevel(parent)) {
            if (_heap.at(index).cmp_key < _heap.at(parent).cmp_key) {
                swap(_heap[index], _heap[parent]);
                _minHeapify(parent);
            } else {
                _maxHeapify(index);
            }
        } else {
            if (_heap.at(index).cmp_key > _heap.at(parent).cmp_key) {
                swap(_heap[index], _heap[parent]);
                _maxHeapify(parent);
            } else {
                _minHeapify(index);
            }
        }
    }

    void _insert(const T &data, const int &cmp_key) {
        _heap.push_back(_HNode(cmp_key, data));
        _size++;
        _minMaxHeapify(_size - 1);
    }

    void _clear() {
        _heap.clear();
        _size = 0;
    }

    void _popMinHeapify(int index) {
        int left = _getLeftChild(index);
        int right = _getRightChild(index);
        if (left >= _size) return; // no child

        // get all grandchildren
        vector<int> grandchildren = {_getLeftChild(left), _getRightChild(left), _getLeftChild(right),
                                     _getRightChild(right)};

        if (grandchildren[0] >= _size) { // no grandchild
            int smaller = (right < _size && _heap[right].cmp_key < _heap[left].cmp_key) ? right : left;
            if (_heap[smaller].cmp_key < _heap[index].cmp_key) {
                swap(_heap[smaller], _heap[index]);
            }
            return;
        }

        int smaller = grandchildren[0];
        for (int i = 1; i < 4; i++) {
            if (grandchildren[i] < _size && _heap[grandchildren[i]].cmp_key < _heap[smaller].cmp_key) {
                smaller = grandchildren[i];
            }
        }
        int parentOfSmaller = _getParent(smaller);
        if (_heap[index].cmp_key > _heap[smaller].cmp_key) {
            swap(_heap[index], _heap[smaller]);
            if (_heap[index].cmp_key > _heap[parentOfSmaller].cmp_key)
                swap(_heap[index], _heap[parentOfSmaller]);
            _popMinHeapify(smaller);
        }
    }

    void _popMaxHeapify(int index) {
        int left = _getLeftChild(index);
        int right = _getRightChild(index);
        if (left >= _size) return; // no child

        // get all grandchildren
        vector<int> grandchildren = {_getLeftChild(left), _getRightChild(left), _getLeftChild(right),
                                     _getRightChild(right)};

        if (grandchildren[0] >= _size) { // no grandchild
            int larger = (right < _size && _heap[right].cmp_key > _heap[left].cmp_key) ? right : left;
            if (_heap[larger].cmp_key > _heap[index].cmp_key) {
                swap(_heap[larger], _heap[index]);
            }
            return;
        }

        int larger = grandchildren[0];
        for (int i = 1; i < 4; i++) {
            if (grandchildren[i] < _size && _heap[grandchildren[i]].cmp_key > _heap[larger].cmp_key) {
                larger = grandchildren[i];
            }
        }
        int parentOfLarger = _getParent(larger);
        if (_heap[index].cmp_key < _heap[larger].cmp_key) {
            swap(_heap[index], _heap[larger]);
            if (_heap[index].cmp_key < _heap[parentOfLarger].cmp_key)
                swap(_heap[index], _heap[parentOfLarger]);
            _popMaxHeapify(larger);
        }
    }

    T _pop_min() {
        T data = _heap[0].data;
        swap(_heap[0], _heap[_size - 1]);
        _heap.pop_back();
        _size--;
        _popMinHeapify(0);

        return data;
    }

    T _pop_max() {
        if (_size == 0) return T();
        if (_size == 1) {
            T data = _heap[0].data;
            _heap.pop_back();
            _size--;
            return data;
        }
        int index = 0;
        int left = _getLeftChild(index);
        int right = _getRightChild(index);
        int larger = (right < _size && _heap[right].cmp_key > _heap[left].cmp_key) ? right : left;
        T data = _heap[larger].data;
        swap(_heap[larger], _heap[_size - 1]);
        _heap.pop_back();
        _size--;
        _popMaxHeapify(larger);

        return data;
    }

   public:
    MinMaxHeap() : _size(0) {}
    ~MinMaxHeap() { _clear(); }
    void clear() { _clear(); }
    bool empty() const { return _size == 0; }
    void setHeap(const vector<T> &arr, const vector<int> &cmp_key_arr) {
        _clear();
        for (int i = 0; i < arr.size(); i++) {
            _heap.push_back(_HNode(cmp_key_arr[i], arr[i]));
        }
        _size = arr.size();
        for (int i = (_size >> 1) - 1; i >= 0; i--) {
            _minMaxHeapify(i);
        }
    }
    void insert(const T &data, const int &cmp_key) { _insert(data, cmp_key); }
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
    T pop_min() { return _pop_min(); }
    T pop_max() { return _pop_max(); }
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

    MaxHeap<int> _maxheap_by_student_count;
    Deap<int> _deap_by_student_count;
    MinMaxHeap<int> _minmaxheap_by_graduate_count;

    string _filename;

    void _clear() {
        _data_arr.clear();
        _deap_by_student_count.clear();
        _maxheap_by_student_count.clear();
        _minmaxheap_by_graduate_count.clear();
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
            data.school_id = stoi(read_line_data_tmp[0]);
            data.school_name = read_line_data_tmp[1];
            data.department_id = stoi(read_line_data_tmp[2]);
            data.department_name = read_line_data_tmp[3];
            data.day_further = read_line_data_tmp[4];
            data.level = read_line_data_tmp[5];
            data.student_count = stoi(read_line_data_tmp[6]);
            data.teacher_count = stoi(read_line_data_tmp[7]);
            data.graduate_count = stoi(read_line_data_tmp[8]);
            _data_arr.push_back(data);
        }

        fin.close();
        return 1;
    }

    void buildDeap() {
        int len = _data_arr.size();
        for (int i = 0; i < len; ++i) {
            _deap_by_student_count.insert(i, _data_arr[i].student_count);
        }

        vector<int> deap = _deap_by_student_count.getDeap();
        int deap_len = deap.size();
        for (int i = 1; i <= deap_len; i++) {
            cout << deap[i - 1] << " ";
            if (floor(log2(i + 1)) != floor(log2(i + 2))) cout << endl;
        }
        cout << endl;
    }

    void buildMaxHeap() {
        int len = _data_arr.size();
        for (int i = 0; i < len; ++i) {
            _maxheap_by_student_count.insert(i, _data_arr[i].student_count);
        }

        vector<int> heap = _maxheap_by_student_count.getHeap();
        int heap_len = heap.size();
        cout << _data_arr[heap[0]].student_count << endl;
        for (int i = 1; i < heap_len; i++) {
            cout << _data_arr[heap[i]].student_count << " ";
            if (floor(log2(i + 1)) != floor(log2(i + 2))) cout << endl;
        }
        cout << endl;
    }

    void buildMinMaxHeap() {
        int len = _data_arr.size();
        for (int i = 0; i < len; ++i) {
            _minmaxheap_by_graduate_count.insert(i, _data_arr[i].graduate_count);
        }

        vector<int> heap = _minmaxheap_by_graduate_count.getHeap();
        int heap_len = heap.size();
        cout << _data_arr[heap[0]].graduate_count << endl;
        for (int i = 1; i < heap_len; i++) {
            cout << _data_arr[heap[i]].graduate_count << " ";
            if (floor(log2(i + 1)) != floor(log2(i + 2))) cout << endl;
        }
        cout << endl;
    }

    void printMaxHeapInfo() {
        if (_maxheap_by_student_count.empty()) {
            return;
        }
        cout << "<max heap>\n";
        cout << "root: [" << _maxheap_by_student_count.top() + 1 << "] "
             << _data_arr[_maxheap_by_student_count.top()].student_count << endl;
        int rightMostIndex, tmp = 0;
        rightMostIndex = _maxheap_by_student_count.getRightMost(tmp);
        int leftMostIndex = 0;
        leftMostIndex = _maxheap_by_student_count.getLeftMost(tmp);

        cout << "bottom: [" << rightMostIndex + 1 << "] " << _data_arr[rightMostIndex].student_count << endl;
        cout << "leftmost bottom: [" << leftMostIndex + 1 << "] " << _data_arr[leftMostIndex].student_count
             << endl;
    }

    void printDeapInfo() {
        if (_deap_by_student_count.empty()) {
            return;
        }
        cout << "<DEAP>\n";

        int rightMostIndex, tmp = 0;
        rightMostIndex = _deap_by_student_count.getRightMost(tmp);
        int leftMostIndex = 0;
        leftMostIndex = _deap_by_student_count.getLeftMost(tmp);

        cout << "bottom: [" << rightMostIndex + 1 << "] " << _data_arr[rightMostIndex].student_count << endl;
        cout << "leftmost bottom: [" << leftMostIndex + 1 << "] " << _data_arr[leftMostIndex].student_count
             << endl;
    }

    void printMinMaxHeapInfo() {
        if (_minmaxheap_by_graduate_count.empty()) {
            return;
        }
        cout << "<min-max heap>\n";
        cout << "root: [" << _minmaxheap_by_graduate_count.top() + 1 << "] "
             << _data_arr[_minmaxheap_by_graduate_count.top()].graduate_count << endl;
        int rightMostIndex, tmp = 0;
        rightMostIndex = _minmaxheap_by_graduate_count.getRightMost(tmp);
        int leftMostIndex = 0;
        leftMostIndex = _minmaxheap_by_graduate_count.getLeftMost(tmp);

        cout << "bottom: [" << rightMostIndex + 1 << "] " << _data_arr[rightMostIndex].graduate_count << endl;
        cout << "leftmost bottom: [" << leftMostIndex + 1 << "] " << _data_arr[leftMostIndex].graduate_count
             << endl;
    }

    void printDeapMinRemoved() {
        if (_deap_by_student_count.empty()) {
            cout << "The Dataset is empty" << endl;
            return;
        }
        int removed = _deap_by_student_count.pop_min();
        cout << "The removed data is: " << removed + 1 << " " << _data_arr[removed].student_count << endl;

        vector<int> deap = _deap_by_student_count.getDeap();
        int deap_len = deap.size();
        for (int i = 1; i <= deap_len; i++) {
            cout << deap[i - 1] << " ";
            if (floor(log2(i + 1)) != floor(log2(i + 2))) cout << endl;
        }
        cout << endl;
    }

    void printDeapMaxRemoved() {
        if (_deap_by_student_count.empty()) {
            cout << "The Dataset is empty" << endl;
            return;
        }
        int removed = _deap_by_student_count.pop_max();
        cout << "The removed data is: " << removed + 1 << " " << _data_arr[removed].student_count << endl;

        vector<int> deap = _deap_by_student_count.getDeap();
        int deap_len = deap.size();
        for (int i = 1; i <= deap_len; i++) {
            cout << deap[i - 1] << " ";
            if (floor(log2(i + 1)) != floor(log2(i + 2))) cout << endl;
        }
        cout << endl;
    }

    void printMinMaxHeapMinRemoved() {
        if (_minmaxheap_by_graduate_count.empty()) {
            cout << "The Dataset is empty" << endl;
            return;
        }
        int removed = _minmaxheap_by_graduate_count.pop_min();
        cout << "The removed data is: " << removed + 1 << " " << _data_arr[removed].graduate_count << endl;

        if (_minmaxheap_by_graduate_count.empty()) {
            cout << "The Heap is cleared." << endl;
            return;
        }

        vector<int> heap = _minmaxheap_by_graduate_count.getHeap();
        int heap_len = heap.size();
        cout << _data_arr[heap[0]].graduate_count << endl;
        for (int i = 1; i < heap_len; i++) {
            cout << _data_arr[heap[i]].graduate_count << " ";
            if (floor(log2(i + 1)) != floor(log2(i + 2))) cout << endl;
        }
        cout << endl;
    }

    void printMinMaxHeapMaxRemoved() {
        if (_minmaxheap_by_graduate_count.empty()) {
            cout << "The Dataset is empty" << endl;
            return;
        }
        int removed = _minmaxheap_by_graduate_count.pop_max();
        cout << "The removed data is: " << removed + 1 << " " << _data_arr[removed].graduate_count << endl;

        if (_minmaxheap_by_graduate_count.empty()) {
            cout << "The Heap is cleared." << endl;
            return;
        }

        vector<int> heap = _minmaxheap_by_graduate_count.getHeap();
        int heap_len = heap.size();
        cout << _data_arr[heap[0]].graduate_count << endl;
        for (int i = 1; i < heap_len; i++) {
            cout << _data_arr[heap[i]].graduate_count << " ";
            if (floor(log2(i + 1)) != floor(log2(i + 2))) cout << endl;
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
            _ds.buildMaxHeap();
            _ds.printMaxHeapInfo();
        }
    }
    void case2() {
        _ds.reset();
        int state = _ds.read();
        while (state < 1) {
            state = _ds.read();
        }
        if (state == 1) {
            _ds.buildDeap();
            _ds.printDeapInfo();
        }
    }
    void case3() {
        _ds.reset();
        int state = _ds.read();
        while (state < 1) {
            state = _ds.read();
        }
        if (state == 1) {
            _ds.buildMinMaxHeap();
            _ds.printMinMaxHeapInfo();
        }
    }

    void case4() {
        if (_ds.isEmpty()) {
            cout << "Please read the data first" << endl;
            return;
        }

        _ds.printDeapMinRemoved();
    }

    void case5() {
        if (_ds.isEmpty()) {
            cout << "Please read the data first" << endl;
            return;
        }

        _ds.printDeapMaxRemoved();
    }

    void case6() {
        if (_ds.isEmpty()) {
            cout << "Please read the data first" << endl;
            return;
        }

        _ds.printMinMaxHeapMinRemoved();
    }

    void case7() {
        if (_ds.isEmpty()) {
            cout << "Please read the data first" << endl;
            return;
        }

        _ds.printMinMaxHeapMaxRemoved();
    }
};

void WriteMenu() {
    cout << "\n******** Heap Construction ********\n"
            "* 0. QUIT                         *\n"
            "* 1. Build a max heap             *\n"
            "* 2. Build a DEAP                 *\n"
            "* 3. Build a minMax heap          *\n"
            "* 4. remove min from a deap       *\n"
            "* 5. remove max from a deap       *\n"
            "* 6. remove min from a minMaxheap *\n"
            "* 7. remove max from a minMaxheap *\n"
            "***********************************\n"
            "Input a choice(0, 1, 2, 3, 4, 5, 6, 7): ";
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
        } else if (command == "3")
            sol.case3();
        else if (command == "4")
            sol.case4();
        else if (command == "5")
            sol.case5();
        else if (command == "6")
            sol.case6();
        else if (command == "7")
            sol.case7();
        else
            cout << "\nCommand does not Exist!!!" << endl;
        WriteMenu();
    }
    // cerr << "Time: " << (double)clock() / (double)CLOCKS_PER_SEC << '\n';
    return 0;
}
