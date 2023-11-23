

#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
// #pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")
#pragma comment(linker, "/stack:200000000")

#include <bits/stdc++.h>
// #include<bits/extc++.h>
using namespace std;

#include <unistd.h>
const int mxbuf = 65536; // default 65536，the less num,the better performance
char OB[mxbuf];
int OP;
inline char RC() {
    static char buf[mxbuf], *p = buf, *q = buf;
    return p == q && (q = (p = buf) + read(0, buf, mxbuf)) == buf ? -1 : *p++;
}
// R, W support negative num
inline int R() {
    static char c;
    bool f = 0;
    int a;
    while ((c = RC()) < '0' && c != '-')
        ;
    if (c == '-') f = 1, c = RC();
    a = c ^ '0';
    while ((c = RC()) >= '0') a *= 10, a += c ^ '0';
    return f ? (-a) : a;
}
inline void W(int n) {
    static char buf[12], p;
    if (n == 0) OB[OP++] = '0';
    p = 0;
    if (n < 0) n = -n, OB[OP++] = '-';
    while (n) buf[p++] = '0' + (n % 10), n /= 10;
    for (--p; p >= 0; --p) OB[OP++] = buf[p];
    OB[OP++] = '\n';
    if (OP > mxbuf - 20) write(1, OB, OP), OP = 0;
}
// can read EOF，return -1
inline int REOF() {
    static char c;
    while ((c = RC()) < 0 && c != 0)
        ;
    if (c == 0) return -1;
    int a = c ^ '0';
    while ((c = RC()) >= '0') a *= 10, a += c ^ '0';
    if (c == 0) return -1;
    return a;
}

template <class T>
long long Mod(T a, T b) {
    return ((a % b) + b) % b;
}
#define endl '\n'
#define ll long long
// #define int long long
#define CHIWAWA                   \
    ios_base::sync_with_stdio(0); \
    cin.tie(0);
#define GETOUT cout.tie(0);
#define gc getchar()

#define cendl putchar('\n');
#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)
template <class T>
bool chmax(T &a, T b) {
    return a < b ? (a = b, 1) : 0;
}
template <class T>
bool chmin(T &a, T b) {
    return a > b ? (a = b, 1) : 0;
}
#define fr(bob, n, l) for (int bob = (n); bob < (l); bob++)
#define fra(ns, a) for (auto(ns) : a)
#define frc(bot, ns, l) for (int bot = (ns); bot <= (l); bot++)
#define frx(i, ns, l) for (int i = (ns); i < (l); i++)
#define mem(arr, initn) memset(arr, initn, sizeof(arr))
#define ALL(va) (va).begin(), (va).end()
#define ALLa(arr) (arr), (arr) + sizeof((arr)) / sizeof((arr)[0])
#define printv(va)                                       \
    {                                                    \
        fr(i, 0, size((va))) { cerr << (va)[i] << ' '; } \
        cendl;                                           \
    }
#define printa(va)                                                           \
    {                                                                        \
        fr(i, 0, sizeof((va)) / sizeof((va)[0])) { cerr << (va)[i] << ' '; } \
        cendl;                                                               \
    }
#define getpos(va, v) lower_bound((v).begin(), (v).end(), (va)) - (v).begin()
#define arrpos(i, va) distance((va), find(ALLa((va)), i))

#define pb emplace_back
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<long double, long double> pdd;
typedef vector<int> vii;
typedef vector<pii> vpi;
typedef vector<pll> vpl;
typedef vector<pdd> vpd;
#define fi first
#define se second
#define setu(x, y, v) set_union(x.begin(), x.end(), y.begin(), y.end(), back_inserter(v))
#define seti(x, y, v) set_intersection(x.begin(), x.end(), y.begin(), y.end(), back_inserter(v))
#define setdu(x, y, v) set_symmetric_difference(x.begin(), x.end(), y.begin(), y.end(), back_inserter(v))
#define setd(x, y, v) set_difference(x.begin(), x.end(), y.begin(), y.end(), back_inserter(v))
#define toupper(s) transform(s.begin(), s.end(), s.begin(), ::toupper)
#define tolower(s) transform(s.begin(), s.end(), s.begin(), ::tolower)

const int MAX = 1e9 + 7;
const int MOD = 998244353;

inline int nextint() {
    int x = 0, w = 1;
    char ch = 0;
    while (ch < '0' || ch > '9') {
        if (ch == '-') w = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') x = (x << 1) + (x << 3) + (ch - '0'), ch = getchar();
    return x * w;
}
inline void writeint(int x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x >= 10) writeint(x / 10);
    putchar(x % 10 + '0');
}

template <class T>
struct Queue {
    stack<T> s1, s2;
    void push(T x) { s1.push(x); }
    void pop() {
        if (s2.empty()) {
            while (!s1.empty()) {
                s2.push(s1.top());
                s1.pop();
            }
        }
        s2.pop();
    }
    T front() {
        if (s2.empty()) {
            while (!s1.empty()) {
                s2.push(s1.top());
                s1.pop();
            }
        }
        return s2.top();
    }
    bool empty() { return s1.empty() && s2.empty(); }
    int size() { return s1.size() + s2.size(); }
};
struct order {
    int OID, Arrival, Duration, Timeout;
    bool operator<(const order &o) const {
        if (Arrival == o.Arrival) {
            return OID < o.OID;
        }
        return Arrival < o.Arrival;
    }
};
struct Cancel {
    int OID, Delay, Time;
};
void order_shell_sort(vector<order> &a) {
    int n = a.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            order temp = a[i];
            int j;
            for (j = i; j >= gap; j -= gap) {
                // a[j]=a[j-gap];
                if (a[j - gap].Arrival == temp.Arrival && a[j - gap].OID > temp.OID) {
                    a[j] = a[j - gap];
                } else if (a[j - gap].Arrival > temp.Arrival) {
                    a[j] = a[j - gap];
                } else {
                    break;
                }
            }
            a[j] = temp;
        }
    }
}
inline void case1(string file) { // file format: 401,402...
    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    ifstream input("input" + file + ".txt");
    string sch;
    for (int i = 0; i < 4; ++i) {
        input >> sch; // read the first row
    }
    int n = 0;
    vector<order> orders;
    while (input >> sch) {
        order o;
        o.OID = stoi(sch);
        input >> o.Arrival >> o.Duration >> o.Timeout;
        orders.push_back(o);
        n++;
    }
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    auto elapsed = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Reading data: " << elapsed << '\n';
    start = chrono::steady_clock::now();
    order_shell_sort(orders);
    end = chrono::steady_clock::now();
    elapsed = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Sorting data: " << elapsed << '\n';
    start = chrono::steady_clock::now();
    ofstream output("sorted" + file + ".txt", ios::out);
    output << "OID\tArrival\tDuration\tTimeOut\n";
    for (int i = 0; i < n; ++i) {
        output << orders[i].OID << '\t' << orders[i].Arrival << '\t' << orders[i].Duration << '\t'
               << orders[i].Timeout << endl;
    }
    end = chrono::steady_clock::now();
    elapsed = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Writing data: " << elapsed << '\n';
    output.close();
    input.close();
}
vector<order> success;
vector<order> fail;

void ProcessOrder(int &now, order o) {
    if (now > o.Timeout) {
        cout << "Order " << o.OID << " is cancelled, now=" << now << endl;
        fail.push_back(o);
        return;
    }
    int finish = now + o.Duration;
    if (finish > o.Timeout) {
        // cancel

        now = o.Timeout;
        cout << "Timeout when processing, Order " << o.OID << " is cancelled, now=" << now << endl;
        fail.push_back(o);
    } else {
        // process

        now = finish;
        cout << "Order " << o.OID << " is processed, now=" << now << endl;
        success.push_back(o);
        // success
    }
}
inline void case2(string file) {
    ifstream input("sorted" + file + ".txt");
    string sch;
    for (int i = 0; i < 4; ++i) {
        input >> sch; // read the first row
    }
    Queue<order> orders;
    int q_mx = 3;
    int now = 0;
    while (input >> sch) {
        order o;
        o.OID = stoi(sch);
        input >> o.Arrival >> o.Duration >> o.Timeout;
        if (now < o.Arrival && orders.empty()) { // idle
            now = o.Arrival;
        }
        if (now > o.Arrival) {
            if (orders.size() < q_mx) {
                orders.push(o);
                cout << "CPU busy, Order " << o.OID << " is enqueued, now=" << now << endl;
            } else {
                cout << "Queue full, Order " << o.OID << " is rejected, now=" << now << endl;
                fail.push_back(o);
                // cancel
            }

            continue;
        }
        int finish = now + o.Duration;
        if (finish > o.Timeout) {
            // cancel

            now = o.Timeout;
            cout << "Timeout when processing, Order " << o.OID << " is cancelled, now=" << now << endl;
            fail.push_back(o);
        } else {
            // process
            if (!orders.empty()) { // CPU busy
                while (!orders.empty()) {
                    order o2 = orders.front();
                    orders.pop();
                    ProcessOrder(now, o2);
                }

                if (now <= o.Arrival) {
                    now = o.Arrival;
                    int finish = now + o.Duration;
                    if (finish > o.Timeout) {
                        // cancel

                        now = o.Timeout;
                        cout << "Timeout when processing, Order " << o.OID << " is cancelled, now=" << now
                             << endl;
                        fail.push_back(o);
                    } else {
                        // process

                        now = finish;
                        cout << "Order " << o.OID << " is processed, now=" << now << endl;
                        success.push_back(o);
                        // success
                    }
                } else {
                    orders.push(o);
                    cout << "CPU busy, Order " << o.OID << " is enqueued, now=" << now << endl;
                }
            } else {
                // CPU idle, so process immediately

                now = finish;
                cout << "CPU idle, Order " << o.OID << " is processed, now=" << now << endl;
                success.push_back(o);
            }
        }
    }

    while (!orders.empty()) {
        order o = orders.front();
        orders.pop();
        ProcessOrder(now, o);
    }

    cout << "\033[1;32m"
         << "Success: ";
    for (auto o : success) {
        cout << o.OID << ' ';
    }
    cout << "\033[0m" << endl;

    cout << "\033[1;31m"
         << "Fail: ";
    for (auto o : fail) {
        cout << o.OID << ' ';
    }
    cout << "\033[0m" << endl;

    input.close();
}
void Menu() {
    cout << "1. Read the input file and sort the orders by arrival time." << endl;
    cout << "2. Process the orders and output the results." << endl;
    cout << "0. Exit." << endl;
    cout << "Please enter your choice: ";
}
signed main() {
    // CHIWAWA;
    // GETOUT;

    int command = 0;
    do {
        Menu();
        cin >> command;
        if (command == 1) {
            string file;
            cout << "Please enter the file number: ";
            cin >> file;
            chrono::steady_clock::time_point start = chrono::steady_clock::now();
            case1(file);
            chrono::steady_clock::time_point end = chrono::steady_clock::now();
            auto elapsed = chrono::duration_cast<chrono::milliseconds>(end - start).count();
            cout << "Time: " << elapsed << '\n';
        } else if (command == 2) {
            string file;
            cout << "Please enter the file number: ";
            cin >> file;
            case2(file);
            success.clear();
            fail.clear();
        }
    } while (command != 0);
    // cerr << "Time: " << (double)clock() / (double)CLOCKS_PER_SEC << '\n';
    return 0;
}