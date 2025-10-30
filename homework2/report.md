# 41343136
作業二:Polynomial Class — 多項式運算

---

## 解題說明

本專案實作 **多項式類別 Polynomial**，以物件導向方式進行多項式的：

1. **加法（Add）**
2. **乘法（Mult）**
3. **代入計算（Eval）**

並支援多項式的**輸入與輸出運算子多載** (`>>`、`<<`)。  
主要展示 C++ 類別設計、動態記憶體配置、以及多項式運算邏輯。

---

## 解題策略

### (1) 類別設計

- **Term 類別**
  - 儲存單項式的「係數 (coef)」與「指數 (exp)」。
  - 宣告為 `Polynomial` 的 friend，以便直接存取。

- **Polynomial 類別**
  - 動態陣列 `termArray` 儲存所有非零項。
  - `capacity` 表示陣列容量。
  - `terms` 表示實際非零項數量。
  - 提供以下成員函式：
    - `Add()`：多項式相加  
    - `Mult()`：多項式相乘  
    - `Eval(x)`：代入 `x` 計算值  
    - `newTerm()`：建立新項（自動擴充容量）

---

### (2) 運算邏輯

#### ➤ 多項式加法 `Add(Polynomial b)`
- 依照指數大小合併兩多項式。
- 若指數相同，合併係數。
- 若不同，指數大的項優先加入結果。

#### ➤ 多項式乘法 `Mult(Polynomial b)`
- 雙層迴圈將每一項交叉相乘。
- 若結果中已有相同指數，則將係數相加。
- 否則新增一個新項。

#### ➤ 代入計算 `Eval(x)`
- 依照指數乘上x次方。
- 並乘上多項式係數。
  計算多項式值。

---

## 程式實作

```cpp
#include <iostream>
#include <cmath>
using namespace std;

class Polynomial;

class Term {
    friend Polynomial;
    friend ostream& operator<<(ostream&, const Polynomial&);
private:
    int exp;
    float coef;
};

class Polynomial {
private:
    Term *termArray;
    int capacity;
    int terms;
public:
    Polynomial() : capacity(2), terms(0) {
        termArray = new Term[capacity];
    }
    ~Polynomial() { delete[] termArray; }

    Polynomial Add(Polynomial b);
    Polynomial Mult(Polynomial b);
    float Eval(float x);
    void newTerm(const float newcoef, const int newexp);

    friend istream& operator>>(istream&, Polynomial&);
    friend ostream& operator<<(ostream&, const Polynomial&);
};
```

（完整程式如 `Polynomial.cpp` 所示）

---

## 使用說明

### ✅ 輸入格式

```
n coef₁ exp₁ coef₂ exp₂ ...
```

例如：
```
3 2 2 3 1 1 0
```
代表多項式：  
> 2x² + 3x + 1

### ✅ 執行流程
1. 讀入兩個多項式 `a`、`b`。  
2. 選擇模式：
   - `1`：執行加法 `a + b`
   - `2`：執行乘法 `a × b`
3. 輸入代入值 `x`，計算多項式結果。

---

## 範例輸入與輸出

### ➤ 範例一：加法

**輸入**
```
3 2 2 3 1 1 0
2 1 1 1 0
1
2
```

**輸出**
```
選擇模式(1.Add,2.Muti):1
2X^2+4X^1+2
輸入X:2
18
```

---

### ➤ 範例二：乘法

**輸入**
```
2 1 1 1 0
2 2 1 1 0
2
2
```

**輸出**
```
選擇模式(1.Add,2.Muti):2
2X^2+3X^1+1
輸入X:2
15
```

---

## 效能分析

| 運算 | 時間複雜度 | 空間複雜度 | 說明 |
|------|--------------|-------------|------|
| Add | O(m + n) | O(m + n) | 逐項比較並合併 |
| Mult | O(m × n) | O(m + n) | 兩兩相乘再合併同次項 |
| Eval | O(n) | O(1) | 單次遍歷計算 |

---

## 測試與驗證

| 測試項目 | 多項式 a | 多項式 b | 操作 | x | 結果 |
|-----------|-----------|-----------|------|---|------|
| 1 | 2x²+3x+1 | x+1 | Add | 2 | 18 |
| 2 | x+1 | 2x+1 | Mult | 2 | 15 |
| 3 | 5x³+2x | 3x² | Add | 1 | 10 |
| 4 | 2x²+1 | x²+x | Mult | 3 | 118 |

---

## 編譯與執行指令

本次作業使用Microsoft Visual Studio 2022編譯及執行

## 結論

1. 成功實作多項式的加法、乘法與代入功能。  
2. 使用動態記憶體自動擴充容量，支援任意項數。  
3. 展現物件導向設計（類別封裝 + 運算子多載）。  
4. 加法與乘法結果皆可正確顯示與計算。  

---

## 申論及開發報告

本作業以物件導向方式實作多項式運算，展示類別封裝與運算子多載的應用。  
程式結構清楚，運算正確，可作為多項式運算教學範例。  
後續可加入微分、減法與排序等功能以擴充應用。
