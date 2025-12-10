# 🟦 2536. Increment Submatrices by One  
**LeetCode — Medium | Difference Array | 2D Prefix Sum**

---

## 📌 Problem Summary

You are given:

- An integer `n` → initial matrix is `n x n`, filled with **0**
- A list of queries → each query is:
- [row1, col1, row2, col2]


For every query, you must **add 1** to all cells inside the submatrix defined by:

- Top-left corner: `(row1, col1)`
- Bottom-right corner: `(row2, col2)`

Your task is to return the matrix after **all** queries are applied.

---

## ❗ Naive vs. Optimal

### ❌ Naive
Loop through each query and update each cell → **O(q * n²)**  
Too slow when `n` is large.

### ✅ Optimal (Using 2D Difference Array)
Use a **2D difference matrix** to mark increments efficiently:

diff[r1][c1] += 1
diff[r1][c2 + 1] -= 1
diff[r2 + 1][c1] -= 1
diff[r2 + 1][c2+1] += 1


Then apply **prefix sums** row-wise → then column-wise to reconstruct the final grid.

This reduces complexity to:

 O(n² + q)

 
---

## 🧠 Why the Difference Matrix Works

Instead of incrementing each cell inside the submatrix, we:

1. Add +1 at the starting point of the region.
2. Subtract 1 outside the boundaries to **cancel the effect**.
3. After taking prefix sums:
   - All intermediate cells naturally accumulate the correct count.

---

## 💻 C++ Code (Optimal & Clean)

```cpp
class Solution {
public:
    vector<vector<int>> rangeAddQueries(int n, vector<vector<int>>& queries) {
        vector<vector<int>> diff(n+1, vector<int>(n+1, 0));

        // Build difference matrix
        for (auto &q : queries) {
            int r1 = q[0], c1 = q[1], r2 = q[2], c2 = q[3];

            diff[r1][c1] += 1;
            diff[r1][c2 + 1] -= 1;
            diff[r2 + 1][c1] -= 1;
            diff[r2 + 1][c2 + 1] += 1;
        }

        // Prefix sum row-wise
        for (int i = 0; i < n; i++) {
            for (int j = 1; j < n; j++) {
                diff[i][j] += diff[i][j - 1];
            }
        }

        // Prefix sum column-wise
        for (int j = 0; j < n; j++) {
            for (int i = 1; i < n; i++) {
                diff[i][j] += diff[i - 1][j];
            }
        }

        // Build final matrix
        vector<vector<int>> ans(n, vector<int>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                ans[i][j] = diff[i][j];
            }
        }

        return ans;
    }
};

```
## ✅ Complexity Analysis

  Operation	Complexity
  
  Applying queries (diff)	O(q)
  
  Row prefix sums	O(n²)
  
  Column prefix sums	O(n²)
  
  Total	O(n² + q)
  
  Space	O(n²)






For each query:


