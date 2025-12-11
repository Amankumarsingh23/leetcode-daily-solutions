# 🟦 3531. Count Covered Buildings  
**LeetCode — Medium | Grid | Geometry | Hash Map**

---

## 📌 Problem Summary

You are given:

- A positive integer **n** → city size is `n × n`
- A list **buildings**, where each entry `buildings[i] = [x, y]` represents a **unique** building at coordinates `(x, y)`

### A building is *covered* if it has at least one building in all **four** directions:

- **Left**  
- **Right**  
- **Above**  
- **Below**

### 🎯 Goal  
Return the **number of covered buildings**.

---

## 🧠 Key Insight

To check coverage for each building `(x, y)`:

### ✔️ It must have another building:
- In the **same row** with a smaller `y` → **left**
- In the **same row**, larger `y` → **right**
- In the **same column**, smaller `x` → **above**
- In the **same column**, larger `x` → **below**

So we:

1. Group buildings **by row and by column**
2. Sort positions within each row and column
3. For each building:
   - Use `lower_bound()` to check neighbors on left/right/above/below efficiently

This gives **O(m log m)** time where `m` = number of buildings.

---

## 💻 C++ Solution (Clean & Optimal)

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countCoveredBuildings(int n, vector<vector<int>>& buildings) {
        unordered_map<int, vector<int>> rows, cols;

        // Group buildings by row and column
        for (auto &b : buildings) {
            int x = b[0], y = b[1];
            rows[x].push_back(y);
            cols[y].push_back(x);
        }

        // Sort each row and column list
        for (auto &p : rows) sort(p.second.begin(), p.second.end());
        for (auto &p : cols) sort(p.second.begin(), p.second.end());

        int covered = 0;

        for (auto &b : buildings) {
            int x = b[0], y = b[1];

            auto &row = rows[x];
            auto &col = cols[y];

            // Find position in row (for left/right)
            auto itRow = lower_bound(row.begin(), row.end(), y);
            bool hasLeft = (itRow != row.begin());
            bool hasRight = (itRow + 1 != row.end());

            // Find position in column (for above/below)
            auto itCol = lower_bound(col.begin(), col.end(), x);
            bool hasAbove = (itCol != col.begin());
            bool hasBelow = (itCol + 1 != col.end());

            if (hasLeft && hasRight && hasAbove && hasBelow)
                covered++;
        }

        return covered;
    }
};
