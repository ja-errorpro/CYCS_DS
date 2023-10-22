// 11127137, 黃乙家
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
#include <iostream>
#include <new>

// #include <list>
// #include <stack>
#include <string>
#include <vector>

using namespace std;

#define endl '\n'

template <typename T> class Stack {
  struct Node {
    T data;
    Node *next;
    Node(const T &d, Node *n = nullptr) : data(d), next(n) {}
  };
  Node *top;
  int _sz;

public:
  Stack() : top(nullptr), _sz(0) {}
  bool empty() const { return top == nullptr; }
  void push(const T &d) {
    try {
      top = new Node(d, top);
      _sz++;
    } catch (bad_alloc &e) {
      cerr << endl
           << "\033[1;31mbad_alloc on stack caught: " << e.what() << "\033[0m"
           << endl;
    }
  }
  void gettop(T &v) {
    if (empty()) {
      cerr << endl << "\033[1;31mStack is empty!\033[0m" << endl;
      return;
    }
    v = top->data;
  }
  void pop() {
    if (empty()) {
      cerr << endl << "\033[1;31mStack is empty!\033[0m" << endl;
      return;
    }
    Node *tmp = top;
    top = top->next;
    delete tmp;
    _sz--;
  }
  int size() { return _sz; }
  ~Stack() {
    while (!empty())
      pop();
  }
};

template <typename T> class List {
  struct Node {
    T data;
    Node *next;
    Node(T d, Node *n = nullptr) : data(d), next(n) {}
  };
  Node *head;
  Node *tail;
  int _sz;

public:
  List() : head(nullptr), tail(nullptr), _sz(0) {}
  List(const List &rhs) : head(nullptr), tail(nullptr), _sz(0) {
    Node *tmp = rhs.head;
    while (tmp != nullptr) {
      push_back(tmp->data);
      tmp = tmp->next;
    }
  }
  bool empty() const { return head == nullptr; }

  void push_back(const T &d) {
    try {
      if (empty()) {
        head = tail = new Node(d);
      } else {
        tail->next = new Node(d);
        tail = tail->next;
      }
      _sz++;
    } catch (bad_alloc &e) {
      cerr << endl
           << "\033[1;31mbad_alloc on list caught: " << e.what() << "\033[0m"
           << endl;
    }
  }
  void push_front(const T &d) {
    try {
      if (empty()) {
        head = tail = new Node(d);
      } else {
        head = new Node(d, head);
      }
      _sz++;
    } catch (bad_alloc &e) {
      cerr << endl
           << "\033[1;31mbad_alloc on list caught: " << e.what() << "\033[0m"
           << endl;
    }
  }
  void front(T &v) {
    if (empty()) {
      cerr << endl << "\033[1;31mList is empty!\033[0m" << endl;
      return;
    }
    v = head->data;
  }
  void back(T &v) {
    if (empty()) {
      cerr << endl << "\033[1;31mList is empty!\033[0m" << endl;
      return;
    }
    v = tail->data;
  }
  void delete_front() {
    if (empty()) {
      cerr << endl << "\033[1;31mList is empty!\033[0m" << endl;
      return;
    }
    Node *tmp = head;
    head = head->next;
    delete tmp;
    _sz--;
  }
  void delete_back() {
    if (empty()) {
      cerr << endl << "\033[1;31mList is empty!\033[0m" << endl;
      return;
    }
    Node *tmp = head;
    while (tmp->next != nullptr) {
      tmp = tmp->next;
    }
    Node *del = tmp;
    tmp = tmp->next;
    delete del;
    _sz--;
  }
  void delete_node(T &v) {
    if (empty()) {
      cerr << endl << "\033[1;31mList is empty!\033[0m" << endl;
      return;
    }

    Node *tmp = head;
    while (tmp != nullptr && tmp->data != v) {
      tmp = tmp->next;
    }

    if (tmp == nullptr) {
      cerr << endl << "\033[1;31mNode not found!\033[0m" << endl;
      return;
    }

    Node *del = tmp;
    tmp = tmp->next;
    delete del;
    _sz--;
  }
  void clear() {
    while (!empty()) {
      delete_front();
    }
  }
  int size() { return _sz; }
  ~List() {
    // cerr << head << endl;
    clear();
  }
};

class Solution {
public:
  /*
  Check if the input is a legal operator
  @ param c: the input character
  @ return: true if it is a legal operator, false otherwise
  */
  bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
  }
  /*
  Check if the input is a legal parenthesis
  @ param c: the input character
  @ return: true if it is a legal parenthesis, false otherwise
  */
  bool isParenthesis(char c) { return c == '(' || c == ')'; }
  /*
  Check if the input is a digit
  @ param c: the input character
  @ return: true if it is a digit, false otherwise
  */
  bool isDigit(char c) { return c >= '0' && c <= '9'; }
  /*
  Check if the input is an operand
  @ param s: the input string
  @ return: true if it is an operand, false otherwise
  */
  bool isOperand(string s) {
    for (char i : s) {
      if (!isDigit(i))
        return false;
    }
    return true;
  }
  /*
  Determine the priority of the operator
  @ param c: the input operator
  @ return: the priority of the operator
  */
  int priority(char c) {
    switch (c) {
    case '+':
    case '-':
      return 1;
    case '*':
    case '/':
      return 2;
    default:
      return 0;
    }
  }
  /*
  Erase all the spaces in the string
  @ param s: the input string
  @ return: the string without spaces
  */
  string SkipSpace(string s) {
    string ret;
    for (char i : s) {
      if (i != ' ')
        ret += i;
    }
    return ret;
  }
  /*
  Check if the input string has any illegal character
  @ param s: the input string
  @ return: true if it is legal, false otherwise
  */
  bool isSymbolLegal(string s) {
    for (char i : s) {
      if (!isOperator(i) && !isDigit(i) && !isParenthesis(i)) {
        cout << "Error 1: " << i << " is not a legitimate character.\n";
        return false;
      }
    }
    return true;
  }
  /*
  Check if the parenthesis is legal
  @ param s: the input string
  @ return: true if it is legal, false otherwise
  */
  bool isParenthesisLegal(string s) {
    int k = 0; // k is the number of open parenthesis minus the number of close
               // parenthesis , k+1 for '(' and k-1 for ')'
    for (char i : s) {
      if (i == '(')
        k++;
      else if (i == ')')
        k--;
      if (k < 0) { // extra close parenthesis
        cout << "Error 2: there is one extra close parenthesis.\n";
        return false;
      }
    }
    if (k > 0) {
      cout << "Error 2: there is one extra open parenthesis.\n";
      return false;
    }
    return true;
  }
  /*
  Check if the input string is a legal infix expression
  @ param s: the input string
  @ return: true if it is legal, false otherwise
  */
  bool isLegalExpression(string s) {
    bool ret = isSymbolLegal(s) && isParenthesisLegal(s);
    if (!ret)
      return false;
    bool inpar = false;
    char prev = ' ';
    for (char i : s) {
      if (i == '(') {
        if (isDigit(prev) || prev == ')') {
          cout << "Error 3: there is one extra operand.\n";
          return false;
        }
        inpar = true;
      } else if (i == ')') {
        if (prev == '(' || isOperator(prev)) {
          cout << "Error 3: it is not infix in the parentheses.\n";
          return false;
        }
        inpar = false;
      } else if (isOperator(i)) {
        if (isOperator(prev) || prev == ' ' || prev == '(') {
          if (inpar)
            cout << "Error 3: it is not infix in the parentheses.\n";
          else
            cout << "Error 3: there is one extra operator.\n";
          return false;
        }
      } else if (isDigit(i)) {
        if (prev == ')') {
          cout << "Error 3: there is one extra operand.\n";
          return false;
        }
      }
      prev = i;
    }

    if (isOperator(prev)) {
      cout << "Error 3: there is one extra operator.\n";
      return false;
    }
    return true;
  }

  /*
  Parse the string into a list of string
  @ param s: the input string
  @ return: the list of string
  */
  List<string> StringParser(string s) {
    List<string> ret;
    string tmp = "";
    for (char i : s) {
      if (isParenthesis(i) || isOperator(i)) {
        if (!tmp.empty()) {
          ret.push_back(tmp);
          tmp = "";
        }
        tmp += i;
        ret.push_back(tmp);
        tmp = "";
      } else if (isDigit(i)) {
        tmp += i;
        /*
        if (tmp > "2147483647") {
          cout << "Error x: the number is too large.\n";
          ret.clear();
          return ret;
        }
        */
      }
    }

    if (!tmp.empty())
      ret.push_back(tmp);
    return ret;
  }

  /*
  Transform the infix expression to postfix expression
  @ param exp: the infix expression
  @ param ret: the postfix expression
  @ return: true if it is successful, false otherwise
  */
  bool InfixToPostfix(List<string> &exp, List<string> &ret) {
    Stack<string> oper;

    // List<string> ret;

    while (!exp.empty()) {
      string cur;
      exp.front(cur), exp.delete_front();
      // cerr << cur << endl;
      if (cur == "(") {
        oper.push(cur);

      } else if (cur == ")") { // -> pop all the operators until "("
        string oper_cur;
        while (!oper.empty()) {
          oper.gettop(oper_cur);
          oper.pop();
          if (oper_cur == "(")
            break;
          ret.push_back(oper_cur);
        }
      } else if (isOperator(cur[0])) {
        string _top = "";
        // higher priority operator must be popped(calculated) first
        if (!oper.empty())
          oper.gettop(_top);

        while (!oper.empty() && priority(_top[0]) >= priority(cur[0])) {
          ret.push_back(_top);
          oper.pop();
          if (!oper.empty())
            oper.gettop(_top);
        }

        oper.push(cur);

      } else if (isOperand(cur)) { // operand can be pushed directly
        ret.push_back(cur);
      }
    }

    string o;
    while (!oper.empty()) { // handle all uncalculated operators
      oper.gettop(o);
      oper.pop();
      if (o != "(")
        ret.push_back(o);
    }

    return true;
  }
  /*
    bool evaluate(List<string> strList, int &ret) {
      ret = 0;
      List<string> tmp = strList;
      Stack<int> s;
      while (!tmp.empty()) {
        string cur;
        tmp.front(cur), tmp.delete_front();
        if (isOperator(cur[0])) {
          int a, b;
          s.gettop(b), s.pop();
          s.gettop(a), s.pop();
          switch (cur[0]) {
          case '+':
            if (a > INT_MAX - b) {
              cout << "Error x: the number is too large.\n";
              return false;
            }
            s.push(a + b);
            break;
          case '-':
            if (a < INT_MIN + b) {
              cout << "Error x: the number is too large.\n";
              return false;
            }
            s.push(a - b);
            break;
          case '*':
            if (a > INT_MAX / b) {
              cout << "Error x: the number is too large.\n";
              return false;
            }
            s.push(a * b);
            break;
          case '/':
            if (b == 0) {
              cout << "Error 4: division by zero.\n";
              return false;
            }
            s.push(a / b);
            break;
          }
        } else {
          int num = atoi(cur.c_str());
          s.push(num);
        }
      }
      s.gettop(ret);
      return true;
    }
    */
};
void WriteMenu() {
  // cout.width(28);

  cout << "\n* Arithmetic Expression Evaluator *" << endl;
  cout << "* 0. QUIT                         *" << endl;
  cout << "* 1. Infix2postfix Transformation *" << endl;
  cout << "***********************************" << endl;
  cout << "Input a choice(0, 1): ";
}
inline void Solve(int task = 1) {

  Solution Sol;
  if (task == 1 || task == 2) {
    string s;
    cout << "\nInput an infix expression: ";
    getline(cin, s);
    s = Sol.SkipSpace(s);
    if (s.empty()) {
      cout << "Error 3: there is one extra operator." << endl;
      return;
    }
    if (!Sol.isLegalExpression(s)) {
      return;
    }

    List<string> strList = Sol.StringParser(s);
    List<string> ret;
    if (!Sol.InfixToPostfix(strList, ret))
      return;
    cout << "It is a legitimate infix expression.\n";
    // cerr << "\033[1;32mInfix To Postfix Passed\033[0m" << endl;

    // int ans;
    // if (Sol.evaluate(ret, ans))
    //   cerr << "\033[1;32mEvaluation: " << ans << "\033[0m" << endl;
    //  cerr << "\033[1;32mEvaluating Passed\033[0m" << endl;
    //  if (task == 2) {
    cout << "Postfix expression: ";
    while (!ret.empty()) {
      string s;
      ret.front(s);
      cout << s << (ret.size() == 1 ? "" : ", ");
      ret.delete_front();
    }
    cout << endl;
    //}
  }
}
signed main() {
  string command;

  // use string to avoid malicious input
  WriteMenu();
  while (cin >> command && command != "0") {
    cin.ignore();
    if (command == "1") {
      Solve(1);
      // cerr << "\033[1;32mTask Passed\033[0m" << endl;
    } else
      cout << "\nCommand does not Exist!!!" << endl;
    WriteMenu();
  }
  // cerr << "Time: " << (double)clock() / (double)CLOCKS_PER_SEC << '\n';
  return 0;
}
