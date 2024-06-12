# 中原資工 Data Structure and Algorithms in C++ 作業檔案

```
聲明：
1. 程式碼已聲明 MIT 授權許可，可自由使用、分享、修改，但根據條款，你必須保留原作者的版權聲明與許可聲明。
2. 程式碼已聲明 GNU GPL v3 授權許可，可自由使用、分享、修改，但根據條款，你必須以同等授權向所有人公開你修改後的程式碼。
2. 此 Repository 僅用於存放作業紀錄，包含程式碼、流程圖，但不包含講解影片。
3. 請不要 Copy-Paste，所有程式碼皆已格式化風格與架構，部分程式碼在效能上進行了各種加速優化，同時也有些程式碼會大幅拖慢效能。
  經過系統測試後結果將與一般寫法差距非常明顯，直接 Copy-Paste 後果自負。
```

# 112-1 Data Structure

## 作業一 [Source Code](./DS1ex1_11127137/DS1ex1_11127137.cpp)
* 任務一：找出迷宮的一個終點
* 任務二：找出迷宮的所有終點
* 任務三：找出到其中一個終點的最短路徑

## 作業二 [Source Code](./DS1ex2_11127137/DS1ex2_11127137.cpp)
* 任務一：判斷中序運算式是否合法
* 任務二：中序運算式轉後序運算式
* 任務三：後序運算式計算結果

## 作業三 [Source Code](./DS1ex3_19_11127137_11127152/DS1ex3_19_11127137_11127152.cpp)
* 任務一：對工作排程以到達時間排序
* 任務二：以 FCFS(First Come First Serve) 策略，單 CPU 模擬排程
* 任務三：以 SQF(Shortest Job First) 策略，二 CPU 模擬排程

## 作業四 [Source Code](./DS1ex4_19_11127137_11127152/DS1ex4_19_11127137_11127152.cpp)
* 任務一：建立兩棵二元搜尋樹，分別以 `number of graduates` 與 `school name` 為 key。
* 任務二：以畢業生數尋找二元搜尋樹中的節點
* 任務三：以學校名稱尋找二元搜尋樹中的節點
* 任務四：以學校名稱尋找兩棵二元搜尋樹中的節點，並刪除該節點

## 作業五 [Source Code](./DS1ex5_19_11127137_11127152/DS1ex5_19_11127137_11127152.cpp)
* 任務一：建立一棵二元搜尋樹，以 `hp` 為 key。
* 任務二：將原陣列轉換成最大堆積，以 `hp` 為 key。
* 任務三：刪除最大堆積中的最大值，並印出刪除的值。

---

# 112-2 Data Structure and Algorithms

## 作業一 [Source Code](./DS2ex1_11127137/DS2ex1_11127137Quiz.cpp)
* 任務一：建立一個最大堆積，以 `student count` 為 key。
* 任務二：建立一個雙端堆積(Deap, Double-Ended Heap)，以 `student count` 為 key。
* 任務三-1：從 Deap 中刪除前 K 大的值並印出。
* 任務三-2：建立一個最小最大堆積(Min-Max Heap)。

## 作業二 [Source Code](./DS2ex2_17_11127137_11127150/DS2ex2_17_11127137_11127150%20Quiz.cpp)
* 任務一：建立一棵 2-3 樹，以 `number of graduates` 為 key，相同 key 需合併為同一節點。
* 任務二：建立一棵 AVL 樹，以 `number of students` 為 key，相同 key 需合併為同一節點。

## 作業三 [Source Code](./DS2ex3_17_11127137_11127150/DS2ex3_17_11127137_11127150Quiz.cpp)
* 任務一：採用 quadratic probing 建立雜湊表，以 student_id 為 key。

tableSize = 比 1.15\*dataSize 大的最小質數。

$$ hash(key) = \Pi student[0..|student|-1] \% tableSize $$

* 任務二：採用 double hashing 建立雜湊表，以 student_id 為 key。

maxStep = 比 dataSize / 5 大的最小質數。

$$ step = maxStep - ( \Pi student[0..|student|-1] \% maxStep) $$

## 作業四 [Source Code](./DS2ex4_17_11127137_11127150/DS2ex4_17_11127137_11127150Quiz.cpp)
* 任務一：給定 (u, v) 以及權重 w，以 Adj List 建立有向圖，list 上的節點需由小到大排序，list 需由大到小排序。
* 任務二：以 BFS 找出每個節點可以到達的節點。
* 任務三：以 DFS 找出權重不小於輸入門檻值，每個節點可以到達的節點。
* 任務四：以 BFS 或 DFS 找出權重不小於隨機門檻值，每個節點可以到達的節點，每個 Edge 的門檻在整個執行過程只隨機一次，並依可到達節點數排序後找出前 K 大的節點。

## 作業五 [Source Code](./DS2ex5_17_11127137_11127150/DS2ex5_17_11127137_11127150Quiz.cpp)
* 任務一：以外部排序法將資料排序，並以二路合併排序法合併，其中 buffer size 指定為 300。
* 任務二：對權重相等的資料建立 Primary Index，紀錄權重值與資料偏移位置。
* 任務三：使 buffer size 可變，做完任務一、二後找到權重不小於輸入門檻值的資料。
