// 11127137, 黃乙家
// If Chinese text cannot normally displays, please view this program with
// UTF-8.
/****************************************************/
/*  CPP Template for School                         */
/*  Author: CompileErr0r(YiJia)                     */
/*  Author ID: 11127137                             */
/*  Compile Environment: Windows 11 64bit MingW-GCC */
/*  Compiler: g++ 9.4                               */
/****************************************************/

#ifdef CONSTOPT

#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
// #pragma GCC optimize("Ofast,unroll-loops,no-stack-protector,fast-math")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")
#pragma comment(linker, "/stack:200000000")

#endif

// #include <bits/stdc++.h>

#include <algorithm>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <istream>
#include <iterator>
#include <list>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <valarray>
#include <vector>

using namespace std;
#define endl '\n'
void WriteMenu() {
  // output menu
  cout.width(28);

  cout << "\n*************************" << endl;
  cout << "* DS homework 1    \t*" << endl;
  cout << "* -Options-     \t*" << endl;
  cout << "* 0. Exit        \t*" << endl;
  cout << "* 1. One goal     \t*" << endl;
  cout << "* 2: More goals  \t*" << endl;
  cout << "* 3: Shortest path  \t*" << endl;
  cout << "*************************" << endl;
  cout << "\n> ";
}
int dx[] = {1, 0, -1, 0}; // right, down, left, up
int dy[] = {0, 1, 0, -1};

class Maze {
private:
  vector<vector<char>> graph;
  int x, y;
  int Goals;
  vector<vector<int>> visited;
  vector<vector<int>> preV;
  int cur_dir;
  vector<deque<pair<int, int>>> paths;
  deque<pair<int, int>> shortestpath;
  deque<pair<int, int>> tmppath;

public:
  Maze() { x = y = cur_dir = Goals = 0; }
  /*
  Clear all data structures.
  */
  void Clear() {
    graph.clear();
    visited.clear();
    paths.clear();
    tmppath.clear();
  }
  /*
  Loads a graph from a file and initializes the necessary data structures.
  @param filename  the file to read
  @param goals  number of goals to find
  @return {boolean}  true if open the file successfully, false otherwise.
  */
  bool Load(string filename, int goals) {
    ifstream f;
    f.open(filename.c_str()); // Before C++11, use f.open(filename.c_str())
    bool chk = f.is_open();
    if (!chk) { // check if the file can be read
      if (filename.size() == 3) {
        filename = "input" + filename + ".txt";
        f.open(filename.c_str());
        if (!f.is_open()) {
          cout << "\nNo such file..." << endl;
          return false;
        }
      } else {
        cout << "\nNo such file..." << endl;
        return false;
      }
    }
    f >> x >> y;     // read two number -> x, y
    graph.resize(y); // dynamic array methods
    visited.resize(y);
    preV.resize(y);
    for (int i = 0; i < y; i++) {
      graph[i].resize(x);
      visited[i].resize(x);
      preV[i].resize(x);
    }

    for (int i = 0; i < y; ++i) {
      for (int j = 0; j < x; ++j) {
        f >> graph[i][j];
        visited[i][j] = false; // At start, All positions is not visited.
        preV[i][j] = 0;
      }
    }

    Goals = goals;
    return true;
  }

  /*
  Performs a DFS starting from the given coordinates
  @param x  The starting x-coordinate
  @param y  The starting y-coordinate
  @return  true if all goals have been reached, false otherwise.
  */
  bool DFS(int x, int y) {
    if (Goals <= 0) // no more goals
      return true;
    if (y < 0 || y >= graph.size())
      return false;
    if (x < 0 || x >= graph[y].size())
      return false;
    if (graph[y][x] == 'O')
      return false;
    if (visited[y][x])
      return false;
    visited[y][x] = true;

    // PrintVisited2();
    // getchar();

    tmppath.push_back(make_pair(x, y));

    if (graph[y][x] == 'G') { // found
      Goals--;
      paths.push_back(tmppath);
    }

    for (int k = 0; k < 4; ++k) {
      int nxt_x = x + dx[cur_dir]; // get next position
      int nxt_y = y + dy[cur_dir];
      DFS(nxt_x, nxt_y); // go straight

      cur_dir = (cur_dir + 1) % 4; // turn right
    }

    // no more path, go back
    tmppath.pop_back();
    return Goals == 0;
  }

  bool DFS_shortestpath(int x, int y) {
    // if (Goals <= 0) // no more goals
    //   return true;
    if (y < 0 || y >= graph.size())
      return false;
    if (x < 0 || x >= graph[y].size())
      return false;
    if (graph[y][x] == 'O')
      return false;

    if (preV[y][x])
      return false;
    if (!shortestpath.empty() && tmppath.size() >= shortestpath.size())
      return false;
    // if (graph[y][x] != 'G')
    preV[y][x]++;

    visited[y][x] = true;

    // PrintVisited3();
    // getchar();

    tmppath.push_back(make_pair(x, y));

    if (graph[y][x] == 'G') { // found
      // paths.push_back(tmppath);
      if (shortestpath.empty() || shortestpath.size() > tmppath.size()) {
        shortestpath = tmppath;
      }
    }

    for (int k = 0; k < 4; ++k) {
      int nxt_x = x + dx[cur_dir]; // get next position
      int nxt_y = y + dy[cur_dir];
      DFS_shortestpath(nxt_x, nxt_y); // go straight

      cur_dir = (cur_dir + 1) % 4; // turn right
    }

    // no more path, go back
    tmppath.pop_back();
    // if (graph[y][x] != 'G')
    preV[y][x]--;
    // PrintVisited3();
    // getchar();
    return false;
  }

  /*
  Print the visited positions in the graph.
  */
  void PrintVisited() {
    for (int i = 0; i < y; ++i) {
      for (int j = 0; j < x; ++j) {
        if (visited[i][j] &&
            graph[i][j] != 'G') // if true, the position has been visited
          cout << 'V';
        else
          cout << graph[i][j];
      }
      cout << endl;
    }
  }

  void PrintVisited2() {
    for (int i = 0; i < y; ++i) {
      for (int j = 0; j < x; ++j) {
        if (visited[i][j] &&
            graph[i][j] != 'G') // if true, the position has been visited
          cout << "\033[1;31mV\033[0m";
        else if (visited[i][j] && graph[i][j] == 'G')
          cout << "\033[1;32mG\033[0m";
        else
          cout << graph[i][j];
      }
      cout << endl;
    }
  }

  void PrintVisited3() {
    for (int i = 0; i < y; ++i) {
      for (int j = 0; j < x; ++j) {
        if (preV[i][j] &&
            graph[i][j] != 'G') // if true, the position has been visited
          cout << "\033[1;31mV\033[0m";
        else if (preV[i][j] && graph[i][j] == 'G')
          cout << "\033[1;32mG\033[0m";
        else
          cout << graph[i][j];
      }
      cout << endl;
    }
  }

  /*
  Print the paths found in the graph.
  */
  void PrintPath() {
    if (paths.empty())
      return; // no path

    for (int i = 0; i < paths.size(); ++i) {   // for each path
      while (!paths[i].empty()) {              // for each position
        pair<int, int> p = paths[i].front();   // get the position
        if (graph[p.second][p.first] != 'G') { // keep the goal
          graph[p.second][p.first] = 'R';      // mark the path
        }
        paths[i].pop_front();
      }
    }

    for (int i = 0; i < y; ++i) {
      for (int j = 0; j < x; ++j) {
        cout << graph[i][j];
      }
      cout << endl;
    }
  }

  void PrintShortestPath() {

    int size = shortestpath.size();
    if (size == 0) {
      cout << "No path found" << endl;
      return;
    }
    while (!shortestpath.empty()) {            // for each position
      pair<int, int> p = shortestpath.front(); // get the position
      if (graph[p.second][p.first] != 'G') {   // keep the goal
        graph[p.second][p.first] = 'R';        // mark the path
      }
      shortestpath.pop_front();
    }

    for (int i = 0; i < y; ++i) {
      for (int j = 0; j < x; ++j) {
        cout << graph[i][j];
      }
      cout << endl;
    }

    cout << "\nShortest path length = " << size << endl;
  }
};

int InputNumber() {
  string Input;

  cin >> Input;

  try {
    int N = atoi(Input.c_str()); // before C++11, use atoi(Input.c_str())
    return N;
  } catch (exception &
               e) { // if stoi throws exception, then treat the input as illegal
    return -1;
  }

  return -1;
}

inline void Solve(bool moreGoals = false) {

  string filename;
  int goals = 1;
  Maze maze;
  do {
    cout << "\nInput a filename >";
    cin >> filename;
    if (moreGoals == true) {

      do {
        cout << "\nInput the number of goals >";
        goals = InputNumber();
        if (goals < 1 || goals > 100)
          cout << "\nILLEGAL input, the number must be in [1, 100]" << endl;
        else
          break;
      } while (goals <= 0 || goals > 100);
    }
  } while (!maze.Load(filename, goals));

  cin.ignore();
  bool suc = maze.DFS(0, 0); // start from (0,0)
  maze.PrintVisited();

  cout << endl;
  if (suc) {
    maze.PrintPath();
  }
}

inline void Solve2() {

  string filename;
  int goals = 1;
  Maze maze;
  do {
    cout << "\nInput a filename >";
    cin >> filename;
  } while (!maze.Load(filename, goals));

  cin.ignore();
  bool suc = maze.DFS_shortestpath(0, 0); // start from (0,0)
  maze.PrintVisited();

  cout << endl;
  maze.PrintShortestPath();
}

int main() {

  string command;
  // use string to avoid malicious input
  WriteMenu();
  while (cin >> command && command != "0") {

    if (command == "1")
      Solve();
    else if (command == "2")
      Solve(true);
    else if (command == "3")
      Solve2();
    else
      cout << "\nCommand does not Exist!!!" << endl;
    WriteMenu();
  }

  // Uncomment below line to measure time
  // cerr << "Time: " << (double)clock() / (double)CLOCKS_PER_SEC << '\n';

  return 0;
}
