# 41343136

作業一：Ackermann 函數與 Power Set

---

## 解題說明

本次作業包含兩個主題：

1. **Ackermann 函數 (Ackermann Function)**  
   要求以遞迴與非遞迴兩種方式實作數學上定義的 Ackermann 函數：

   $$
   A(m, n) =
   \begin{cases}
   n + 1, & \text{if } m = 0 \\
   A(m - 1, 1), & \text{if } n = 0 \\
   A(m - 1, A(m, n - 1)), & \text{otherwise}
   \end{cases}
   $$

2. **Power Set（冪集合）**  
   要求使用遞迴方式列出集合的所有子集合。  

---

## 解題策略

### (1) Ackermann 函數

- **遞迴版本**  
  直接依據數學定義轉為遞迴呼叫，對應三種情況：
  - 當 `m == 0`，回傳 `n + 1`
  - 當 `n == 0`，回傳 `A(m - 1, 1)`
  - 其他情況則呼叫 `A(m - 1, A(m, n - 1))`

- **非遞迴版本（無 stack）**  
  因 Ackermann 函數遞迴層數極深，若完全展開會導致 Stack Overflow。  
  因此以**數學化簡公式**取代一般遞迴運算（僅適用 m ≤ 3）：
  - A(0, n) = n + 1  
  - A(1, n) = n + 2  
  - A(2, n) = 2n + 3  
  - A(3, n) = 2^(n + 3) - 3

---

### (2) Power Set（遞迴版本）

- 使用遞迴方法列出所有子集合。  
- 每一層遞迴決定「是否包含當前元素」。  
- 使用靜態布林陣列 `chosen[]` 紀錄是否選取該元素。  
- 終止條件：當 index == n 時，輸出一個子集合。

---

## 程式實作

### (1) Ackermann 函數（遞迴版）

```cpp
#include <iostream>
using namespace std;
int Ack(int m, int n) 
{
    if (m == 0)
        return n + 1;
    else if (n == 0)
        return Ack(m - 1, 1);
    else
        return Ack(m - 1, Ack(m, n - 1));
}
int main() 
{
    int m, n;
    cout << "輸入 m 和 n: ";
    cin >> m >> n;
    cout << "A(" << m << ", " << n << ") = " << Ack(m, n) << endl;
    return 0;
}


```

---

### (2) Ackermann 函數（非遞迴版，無 stack）

```cpp
#include <iostream>
#include <cmath>
using namespace std;
int Ack(int m, int n) {
    if (m == 0) return n + 1;
    else if (m == 1) return n + 2;
    else if (m == 2) return 2 * n + 3;
    else if (m == 3) return pow(2, n + 3) - 3;
    else if (m == 4 && n == 0) return 13;
    else
    {
        cout << "數值太大，無法處理。" << endl;
        return -1;
    }
}

int main() {
    int m, n;
    cout << "輸入 m 和 n: ";
    cin >> m >> n;
    int result = Ack(m, n);
    if (result != -1)
        cout << "Ackermann(" << m << ", " << n << ") = " << result << endl;
    return 0;
}
```

---

### (3) Power Set（遞迴版，動態陣列，無 subset[]）

```cpp
#include <iostream>
using namespace std;

void powerSet(char* set, int n, int index) 
{
    static bool chosen[100] = { false }; 


    if (index == n) 
    {
        cout << "{ ";
        for (int i = 0; i < n; i++) 
        {
            if (chosen[i]) cout << set[i] << " ";
        }
        cout << "}" << endl;
        return;
    }


    chosen[index] = false;
    powerSet(set, n, index + 1);


    chosen[index] = true;
    powerSet(set, n, index + 1);
}

int main() 
{
    int n;
    cout << "輸入集合大小 n: ";
    cin >> n;
    char* set = new char[n];
    cout << "請輸入 " << n << " 個元素（例如 a b c）: ";
    for (int i = 0; i < n; i++) 
    {
        cin >> set[i];
    }
    cout << "\nPower set:" << endl;
    powerSet(set, n, 0);
    delete[] set;
    return 0;
}
```

---

## 效能分析

| 題目 | 時間複雜度 | 空間複雜度 | 備註 |
|------|--------------|-------------|------|
| Ackermann (遞迴) | 極高 (超指數級) | O(m+n) | 遞迴層數極深 |
| Ackermann (非遞迴) | O(1) (m≤3)or(m=4,n=0) | O(1) | 直接套用數學公式 |
| Power Set (遞迴) | O(2ⁿ × n) | O(n) | 每層遞迴二分支 |

---

## 測試與驗證

### 測試案例

#### Ackermann 函數

| 測試案例 | 輸入 (m, n) | 預期輸出 | 實際輸出 |
|-----------|--------------|-----------|-----------|
| 測試一 | (0, 3) | 4 | 4 |
| 測試二 | (1, 2) | 4 | 4 |
| 測試三 | (2, 3) | 9 | 9 |
| 測試四 | (3, 2) | 29 | 29 |
| 測試五 | (4, 0) | 13 | 13 |
| 測試六 | (4, 1) | 超出可計算範圍 | 超出可計算範圍 |


#### Power Set

| 測試案例 | 輸入集合 | 預期輸出 (部分) |
|-----------|------------|----------------|
| 測試一 | {a} | {}, {a} |
| 測試二 | {a, b} | {}, {a}, {b}, {a,b} |
| 測試三 | {a, b, c} | {}, {a}, {b}, {c}, {a,b}, {a,c}, {b,c}, {a,b,c} |

---

### 編譯與執行指令

```bash
$ g++ -std=c++17 -o ackermann ackermann.cpp
$ ./ackermann

$ g++ -std=c++17 -o powerset powerset.cpp
$ ./powerset
```

---

## 結論

1. **Ackermann 函數**  
   - 成功以遞迴及非遞迴方式實作。  
   - 遞迴版本展示深層遞迴特性；非遞迴版本則以數學化簡公式取代實際展開。  

2. **Power Set**  
   - 遞迴邏輯清楚，每層處理「包含 / 不包含」決策。  
   - 能正確輸出所有子集合。  

3. **整體表現**  
   - 兩題皆展現遞迴思維：將大問題拆解為子問題逐層解決。  

---

## 申論及開發報告

### 遞迴的使用原因

1. **結構清晰且符合數學定義**  
   遞迴能自然表達「由小到大」的關係，特別適合 Ackermann 與 Power Set 這類具有自我參照的數學函式。

2. **程式邏輯簡潔明確**  
   遞迴不需額外資料結構即可處理多層決策，邏輯直觀。
