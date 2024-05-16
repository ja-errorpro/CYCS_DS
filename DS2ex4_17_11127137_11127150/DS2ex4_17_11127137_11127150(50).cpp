// 11127137 黃乙家, 11127150 張睿恩
/****************************************************/
/*  CPP Template for School                         */
/*  Author: CompileErr0r(YiJia)                     */
/*  Author ID: 11127137                             */
/*  Compile Environment: Linux 5.15.90.1 WSL x86_64 */
/*  Compiler: g++ 9.4                               */
/****************************************************/

#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream> 
#include <string>
#include <vector>
#include <queue>
#include <algorithm>


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


struct Edge {
    string getID;
    float weight;
};


struct Vertex {
    string putID;
    vector<Edge> edges;
};


class AdjacencyLists {
private:
	string input_file_name;
    string output_file_name;
    string file_number;
	vector<Vertex> adjList;

	// 尋找該put_ID是否以建立 
    int findVertex(string id) {
        for (int i = 0; i < adjList.size(); i++) {
            if (adjList[i].putID == id) {
                return i;
            }
        }
        
        return -1;
    }
    
    // 排序 edges 
	void sortEdges(vector<Edge>& edges) {
        for (int i = 0; i < edges.size(); ++i) {
            for (int j = i + 1; j < edges.size(); ++j) {
                if (edges[j].getID < edges[i].getID) {
                    swap(edges[i], edges[j]);
                }
            }
        }
    }
	
	// 排序  Vertex
    void sortVertices(vector<Vertex>& vertices) {
        for (int i = 0; i < vertices.size(); ++i) {
            for (int j = i + 1; j < vertices.size(); ++j) {
                if (vertices[j].putID < vertices[i].putID) {
                    swap(vertices[i], vertices[j]);
                }
            }
        }
    }
    
    
	// 排序工作 
    void sortAdjacencyList() {
        for (int i = 0; i < adjList.size(); i++) {
            sortEdges(adjList[i].edges);
        }
        sortVertices(adjList);
    }

    
    string removeSpaces(const string& str) {
        string result;
        for (char c : str) {
            if (!isspace(c)) {
                result += c;
            }
        }
        return result;
    }
    
    /*
	void BFS(const string& startID) {

    }
    */
    
public:
	
	void clear() {
		adjList.clear();
		input_file_name.clear();
    	output_file_name.clear();
    	file_number.clear();
    }
    
	int read() {
        if (input_file_name.empty()) {
            cout << "\nInput a file number ([0] Quit): ";
            cin >> file_number;
            cin.ignore();
            if (file_number == "0") return -2;
            input_file_name = "pairs" + file_number + ".bin";
        }
        
        ifstream fin(input_file_name, ios::binary);
        if (!fin.is_open()) {
            cout << "\n### " << input_file_name << " does not exist! ###" << endl;
        	return -1;
		}
		
		char putID[12];
        char getID[12];
        float weight;

        while (fin.read(putID, sizeof(putID))) {
            fin.read(getID, sizeof(getID));
            fin.read((char*)&weight, sizeof(float));
			
			/* 
			putID[11] = '\0';
			getID[11] = '\0';
			*/
			 
            string putID_str(putID, 12) ;
            string getID_str(getID, 12) ;
			putID_str = removeSpaces(putID);
			getID_str = removeSpaces(getID);
			
			int put_Index = findVertex(putID_str);
            
            if (put_Index == -1) {
                Vertex newVertex{putID_str};
                adjList.push_back(newVertex);
                put_Index = adjList.size() - 1;
            }

            Edge newEdge{getID_str, weight};
            adjList[put_Index].edges.push_back(newEdge);

			int get_Index = findVertex(getID_str);
            if (get_Index == -1) {
                Vertex newVertex{getID_str};
                adjList.push_back(newVertex);
            }
            
        }
        
        fin.close();
        sortAdjacencyList();
        return 0;
    }
    
    void writeAdjacencyList() {
        output_file_name = "pairs" + file_number + ".adj";
        ofstream outFile(output_file_name);
        
        for (int i = 0; i < adjList.size(); i++) {
            outFile << "[" << setw(2) << i + 1 << "] " << adjList[i].putID << endl;
            for (int j = 0; j < adjList[i].edges.size(); j++) {
                outFile << "(" << setw(2) << j + 1 << ") " << adjList[i].edges[j].getID << ", " << fixed << setprecision(2) << adjList[i].edges[j].weight << " ";
            }
            outFile << endl;
        }
    }
    
    void printGraphStatistics() {
        int totalIDs = adjList.size();
        int totalNodes = 0;
        
        for (int i = 0; i < adjList.size(); i++) {
            totalNodes = totalNodes + adjList[i].edges.size();
        }
        
    	cout << endl << "<<< There are " << totalIDs << " IDs in total. >>>" << endl;
        cout << endl << "<<< There are " << totalNodes << " nodes in total. >>>" << endl;
	}
	
    

    
};


class Solution {
	AdjacencyLists adjList;
	
   public:
    Solution() {}
    void case1() {
        adjList.clear();
        if(!adjList.read()) {
        	adjList.printGraphStatistics();
        	adjList.writeAdjacencyList();	
		}
    }

    void case2() {
		// if 
    }
};
void WriteMenu() {
    cout << "\n**** Graph data manipulation *****\n"
            "* 0. QUIT                          *\n"
            "* 1. Build adjacency lists         *\n"
            "* 2. Compute connection counts     *\n"
            "************************************\n"
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
