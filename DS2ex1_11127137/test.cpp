/**電資三 10720138 陳尚宏 DSex110720138 **/

#include <math.h>
#include <time.h>

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

typedef struct HeapNode {
    string schNum, schName, majorNum, majorName, genre, DayNight, Edu, City;
    int sNum, tNum, gradu, Seq;

    HeapNode()
        : schNum(""),
          schName(""),
          majorNum(""),
          majorName(""),
          genre(""),
          DayNight(""),
          Edu(""),
          City(""),
          sNum(-1),
          tNum(-1),
          gradu(-1),
          Seq(-1){};

    HeapNode(string a, string b, string c, string d, string e, string f, string g, string h, int i, int j,
             int k, int l)
        : schNum(a),
          schName(b),
          majorNum(c),
          majorName(d),
          genre(e),
          DayNight(f),
          Edu(g),
          City(h),
          sNum(i),
          tNum(j),
          gradu(k),
          Seq(l){};

} Node;

vector<string> vecSrc;
vector<string> vecSplit;
vector<Node> temp;
/** Note

Apply array-based data structure to implement Heap

Fundamental Heap-related data structures implementation

Project list:(list by Sequence)
------------------
Readfile

Max Heap:
func: insert one by one (f)
      delete

MinMaxHeap:
func: insert one by one (f)
      delete

Double-ended Priority Queue (Deap):
func: insert one by one (f)
      delete

binomial heap

Fibonacci Heap

main

**/

int Left(int i) { return (2 * i + 1); }

int Right(int i) { return (2 * i + 2); }

int Parent(int i) { return (i - 1) / 2; }

int grandParent(int i) { return (i + 1) / 4 - 1; }

int Floor(int cur) {
    int f = log2(cur + 1) + 1;
    return f;
}

int Size(vector<Node> &vec) { return vec.size(); }

int bottom(vector<Node> &vec) { return vec.size() - 1; }

int leftmost(vector<Node> &vec) {
    int i = 0;
    while (((int)pow(2, i)) < Size(vec) + 1) {
        i++;
    }
    return (int)pow(2, i - 1) - 1;
}

int my_split(const string &src, const char &delim, vector<string> &vec) {
    int src_len = src.length();
    int find_cursor = 0;
    int read_cursor = 0;

    if (src_len <= 0) return -1;

    vec.clear();

    while (read_cursor < src_len) {
        find_cursor = src.find(delim, find_cursor);

        if (-1 == find_cursor) {
            if (read_cursor <= 0) return -1;

            if (read_cursor < src_len) {
                vec.push_back(src.substr(read_cursor, src_len - read_cursor));
                return 0;
            }
        }

        else if (find_cursor == read_cursor && (read_cursor != 0))
            vec.push_back(string(""));

        else
            vec.push_back(src.substr(read_cursor, find_cursor - read_cursor));

        read_cursor = ++find_cursor;

        if (read_cursor == src_len) {
            vec.push_back(string(""));
            return 0;
        }
    } // end while()
}

bool readfile(string filename) {
    filename = "input" + filename + ".txt";
    cout << filename << endl;
    ifstream fin(filename.c_str());

    if (!fin) {
        cout << "read file failed!\n\n";
        return false;
    }
    string s;

    if (fin) {
        int count = 1;

        for (int i = 0; i < 2; i++) getline(fin, s);

        while (getline(fin, s)) {
            // title=s;
            break;
        }

        while (getline(fin, s)) {
            vecSrc.push_back(s);

            for (string src : vecSrc) {
                Node arr;
                vecSplit.clear();

                int iRet = my_split(src, '\t', vecSplit);

                arr.schNum = vecSplit[0];

                arr.schName = vecSplit[1];

                arr.majorNum = vecSplit[2];

                arr.majorName = vecSplit[3];

                arr.DayNight = vecSplit[4];

                arr.Edu = vecSplit[5];

                vecSplit[6].erase(remove(vecSplit[6].begin(), vecSplit[6].end(), '"'), vecSplit[6].end());
                vecSplit[6].erase(remove(vecSplit[6].begin(), vecSplit[6].end(), ','), vecSplit[6].end());
                arr.sNum = atoi(vecSplit[6].c_str());

                vecSplit[7].erase(remove(vecSplit[7].begin(), vecSplit[6].end(), '"'), vecSplit[7].end());
                vecSplit[7].erase(remove(vecSplit[7].begin(), vecSplit[6].end(), ','), vecSplit[7].end());
                arr.tNum = atoi(vecSplit[7].c_str());

                vecSplit[8].erase(remove(vecSplit[8].begin(), vecSplit[8].end(), '"'), vecSplit[8].end());
                vecSplit[8].erase(remove(vecSplit[8].begin(), vecSplit[8].end(), ','), vecSplit[8].end());
                arr.gradu = atoi(vecSplit[8].c_str());

                arr.City = vecSplit[9];

                arr.genre = vecSplit[10];

                arr.Seq = count;
                count++;

                temp.push_back(arr);
            }
            vecSrc.clear();
        }
        count = 0;
    }
    return true;
}

/******************************************** MaxHeap *****************************************************/
class MaxHeap {
   private:
    vector<Node> Maxvec;

   public:
    MaxHeap() {}

    string title;

    void adjust_up(int cur) {
        while (cur > 0) {
            if (Maxvec[cur].sNum < Maxvec[Parent(cur)].sNum)
                break;
            else
                swap(Maxvec[cur], Maxvec[Parent(cur)]);
            cur = Parent(cur);
        }
    }

    void access() {
        for (int i = 0; i < temp.size(); i++) {
            Maxvec.push_back(temp[i]);
            adjust_up(bottom(Maxvec));
        }
        temp.clear();
    }

    /*void deletef()
     {
         string num;
         //int cur=searchf(num);
         vecAssign(Maxvec[cur],Maxvec[bottom]);
         Maxvec.pop_back();
         if(bottom > 1){
             if(Maxvec[cur].sNum > Maxvec[Parent(cur)].sNum && cur>1)
                 adjust_up(cur);
             else
                 adjust_down(cur);
         }

     }//end delete

     int searchf(string num){

         int flag=0; // find init
         for(int i=0;i<Size(Maxvec)-1;i++){
             if(Maxvec[i].sNum==atoi(num))
             {
                 flag=1;
                   break;
             }
         }

         if(flag==1)
             return i;
         else{
             cout<<"Data not found!!\n";
             return -1;
         }
     }//end search

     bool isMaxhp(){

     }

     void adjust_down(){

         while(cur<=bottom(Maxvec))
         {
             if((cur < bottom(Maxvec))&& (Maxvec[cur] <Maxvec[cur+1]))
                 cur++;
             if(>=Maxvec[cur])
                 break;
             else{
                 Max
             }
         }
     }*/

    void Clear() { Maxvec.clear(); }

    void ShowHeap() {
        /*for(int i=0; i<Maxvec.size(); i++)
            cout<<Maxvec[i].sNum<<"\t";*/
        cout << "\n <Max Heap>" << endl;
        cout << "Data Size= " << Size(Maxvec) << endl;
        cout << "\nRoot= "
             << "[" << Maxvec[0].Seq << "] " << Maxvec[0].sNum << endl;
        cout << "bottom= "
             << "[" << Maxvec[bottom(Maxvec)].Seq << "] " << Maxvec[bottom(Maxvec)].sNum << endl;
        cout << "leftmost= "
             << "[" << Maxvec[leftmost(Maxvec)].Seq << "] " << Maxvec[leftmost(Maxvec)].sNum << endl;
        Maxvec.clear();
        cout << endl;
    }

}; /// End class MaxHeap

// void Huffman(){};
/******************************************** MinMaxHeap
 * *****************************************************/
class MMHeap {
   private:
    vector<Node> MMvec;

   public:
    void access() {
        for (int i = 0; i < temp.size(); i++) {
            MMvec.push_back(temp[i]);
            BubbleUp(bottom(MMvec));
        }
        temp.clear();
    }

    MMHeap() {}

    string title;

    bool is_min_level(int cur) {
        if (Floor(cur) % 2 == 1) return true;
        return false;
    }

    void BubbleUp(int cur) {
        if (is_min_level(cur)) {
            if (MMvec[Parent(cur)].sNum < MMvec[cur].sNum) {
                swap(MMvec[Parent(cur)], MMvec[cur]);
                BubbleUpMax(Parent(cur));
            } else {
                BubbleUpMin(cur);
            }
        }

        else {
            if (MMvec[Parent(cur)].sNum > MMvec[cur].sNum) {
                swap(MMvec[Parent(cur)], MMvec[cur]);
                BubbleUpMin(Parent(cur));
            } else {
                BubbleUpMax(cur);
            }
        }
    }

    void BubbleUpMin(int cur) {
        while (cur > 2) {
            if (MMvec[grandParent(cur)].sNum > MMvec[cur].sNum) {
                swap(MMvec[grandParent(cur)], MMvec[cur]);
                cur = grandParent(cur);
            } else
                break;
        }
    }

    void BubbleUpMax(int cur) {
        while (cur > 2) {
            if (MMvec[grandParent(cur)].sNum < MMvec[cur].sNum) {
                swap(MMvec[grandParent(cur)], MMvec[cur]);
                cur = grandParent(cur);
            } else
                break;
        }
    }

    void Clear() { MMvec.clear(); }

    void ShowHeap() {
        /*for(int i=1; i<Dvec.size(); i++)
        {
            cout<<Dvec[i].sNum<<"\t";
            if(Floor(i+1) != Floor(i))
                cout<<"\n";
        }*/
        cout << "\n <MinMaxHeap> " << endl;
        cout << "Data Size= " << Size(MMvec) << endl;
        cout << "\nRoot= "
             << "[" << MMvec[0].Seq << "] " << MMvec[0].sNum << endl;
        cout << "bottom= "
             << "[" << MMvec[bottom(MMvec)].Seq << "] " << MMvec[bottom(MMvec)].sNum << endl;
        cout << "leftmost= "
             << "[" << MMvec[leftmost(MMvec)].Seq << "] " << MMvec[leftmost(MMvec)].sNum << endl;
        MMvec.clear();
        cout << endl;
    }

}; /// End MinMaxHeap

/************************************************************* Deap
 * *********************************************************/
class Deap {
   private:
    vector<Node> Dvec;

   public:
    void access() {
        Dvec.push_back(Node());
        for (int i = 0; i < temp.size(); i++) {
            Dvec.push_back(temp[i]);
            Deapify();
        }
        temp.clear();
    }

    Deap() {}

    string title;

    int MinRoot() { return 1; }

    int MaxRoot() { return 2; }

    void Max_adjust_up(int cur) {
        while (cur > 2) {
            if (Dvec[cur].sNum < Dvec[Parent(cur)].sNum)
                break;
            else
                swap(Dvec[cur], Dvec[Parent(cur)]);
            cur = Parent(cur);
        }

    } /// End Max_adjust_up

    void Min_adjust_up(int cur) {
        while (cur > 2) {
            if (Dvec[cur].sNum > Dvec[Parent(cur)].sNum)
                break;
            else
                swap(Dvec[cur], Dvec[Parent(cur)]);
            cur = Parent(cur);
        }

    } /// End Min_adjust_up

    bool IsAtMin(int cur) {
        while (Parent(cur) != 0) {
            cur = Parent(cur);
        }
        if (cur == MinRoot()) {
            return true;
        }

        else
            return false;

    } /// End IsAtMin

    int corr_find(int cur) /// correspond node
    {
        int floor = log2(cur + 1) + 1;
        int corr;

        if (!IsAtMin(cur)) {
            corr = cur - pow(2, floor - 2);
        }

        if (IsAtMin(cur)) {
            corr = cur + pow(2, floor - 2);
            if (corr > Size(Dvec) - 1) corr = Parent(corr);
        }

        return corr;

    } /// End Min_corr_find

    void Deapify() {
        if (!IsAtMin(bottom(Dvec)) && bottom(Dvec) > 1) {
            if (Dvec[bottom(Dvec)].sNum < Dvec[corr_find(bottom(Dvec))].sNum) {
                swap(Dvec[bottom(Dvec)], Dvec[corr_find(bottom(Dvec))]);
                Min_adjust_up(corr_find(bottom(Dvec)));
            }

            else {
                Max_adjust_up(bottom(Dvec));
            }
        }

        if (IsAtMin(bottom(Dvec)) && bottom(Dvec) > 1) {
            if (Dvec[bottom(Dvec)].sNum > Dvec[corr_find(bottom(Dvec))].sNum) {
                swap(Dvec[bottom(Dvec)], Dvec[corr_find(bottom(Dvec))]);
                Max_adjust_up(corr_find(bottom(Dvec)));
            }

            else {
                Min_adjust_up(bottom(Dvec));
            }
        }

    } /// End Heapify

    void Clear() { Dvec.clear(); }

    void ShowHeap() {
        int floor = 1;
        for (int i = 1; i < Dvec.size(); i++) {
            cout << Dvec[i].sNum << "\t";
            if (Floor(i + 1) != Floor(i)) cout << "\n";
        }
        cout << "\n <Deap> " << endl;
        cout << "Data Size= " << Size(Dvec) << endl;
        cout << "bottom= "
             << "[" << Dvec[bottom(Dvec)].Seq << "] " << Dvec[bottom(Dvec)].sNum << endl;
        cout << "leftmost= "
             << "[" << Dvec[leftmost(Dvec)].Seq << "] " << Dvec[leftmost(Dvec)].sNum << endl;
        Dvec.clear();
        cout << endl;
    }

}; /// End Deap

class binoHeap {
   private:
    vector<Node> Bvec;

   public:
};

class FiboHeap {
   private:
    vector<Node> Fibo;

   public:
};

void vecAssign(struct vector<Node> &V1, struct vector<Node> &V2) { V1 = V2; }

int main() {
    cout << "@ Author: 電資三 10720138 陳尚宏 \n" << endl;
    int choice;
    string filename;

    MaxHeap Max;
    Deap D;
    MMHeap M;
    binoHeap bi;
    FiboHeap fi;

    while (1) {
        cout << "**** Heap Construction *****\n"
             << "* 0. QUIT                  *\n"
             << "* 1. Build a max heap      *\n"
             << "* 2. Build a DEAP          *\n"
             << "* 3. Build a MinMaxHeap    *\n"
             << "*************************************\n"
             << "Input a choice(0, 1, 2, 3): ";
        cin >> choice;
        if (choice != 1 && choice != 2 && choice != 3 && choice != 0) {
            cout << "\nCommand does not exist!\n" << endl;
            continue;
        } else if (choice == 0)
            exit(0);

        cout << "\nInput a file number ([0] Quit): ";
        cin >> filename;
        if (filename == "0") exit(0);

        clock_t Time1, Time2;

        vector<Node> temp1;
        double time[10], sum = 0;
        int i = 0;
        if (readfile(filename) == false) continue;

        switch (choice) {
            case 0:
                return 0;

            case 1:
                vecAssign(temp1, temp);
                while (i < 10) {
                    Time1 = clock();
                    Max.access();
                    Time2 = clock();
                    Max.Clear();
                    time[i] = (double)(Time2 - Time1) / CLOCKS_PER_SEC;
                    vecAssign(temp, temp1);
                    cout << "第" << i + 1 << "次 " << time[i] << endl;
                    i++;
                }

                temp1.clear();
                Max.access();
                Max.ShowHeap();
                for (int i = 0; i < 10; i++) {
                    sum += time[i];
                }
                sum = sum / 10;
                cout << "Input" << filename << " average heapify time: " << sum << endl << endl;
                temp.clear();
                break;

            case 2:
                vecAssign(temp1, temp);
                while (i < 10) {
                    Time1 = clock();
                    D.access();
                    Time2 = clock();
                    D.Clear();
                    time[i] = (double)(Time2 - Time1) / CLOCKS_PER_SEC;
                    vecAssign(temp, temp1);
                    cout << "第" << i + 1 << "次 " << time[i] << endl;
                    i++;
                }

                temp1.clear();
                D.access();
                D.ShowHeap();
                for (int i = 0; i < 10; i++) {
                    sum += time[i];
                }
                sum = sum / 10;
                cout << "Input" << filename << " average heapify time: " << sum << endl << endl;
                temp.clear();
                break;

            case 3:
                vecAssign(temp1, temp);
                while (i < 10) {
                    Time1 = clock();
                    M.access();
                    Time2 = clock();
                    M.Clear();
                    time[i] = (double)(Time2 - Time1) / CLOCKS_PER_SEC;
                    vecAssign(temp, temp1);
                    cout << "第" << i + 1 << "次 " << time[i] << endl;
                    i++;
                }

                temp1.clear();
                M.access();
                M.ShowHeap();
                for (int i = 0; i < 10; i++) {
                    sum += time[i];
                }
                sum = sum / 10;
                cout << "Input" << filename << " average heapify time: " << sum << endl << endl;
                temp.clear();
                break;

            default:
                cout << "Command does not exist!\n";
                break;

        } /// end switch

    } /// End while
}