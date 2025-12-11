# 🟦 474. Ones and Zeroes  
**LeetCode — Medium | DP | 0/1 Knapsack**

---

## 📌 Problem Summary

You are given:

- An array of **binary strings** `strs`
- Two integers:
  - `m` → maximum number of **0's** allowed  
  - `n` → maximum number of **1's** allowed  

### 🎯 Goal  
Find the **size of the largest subset** of `strs` such that:

- Total 0’s ≤ `m`
- Total 1’s ≤ `n`

This is exactly like a **0/1 knapsack problem**, but with **two weights**  
→ number of zeros & number of ones.

---

## 🧠 Key Idea: 2D 0/1 Knapsack

For each string:

- Count number of zeros → `zeros`
- Count number of ones → `ones`

We maintain a DP table:

    dp[i][j] = max number of strings we can pick
    
using at most i zeros and j ones


For each string, we update DP **backwards** (important!) to avoid reusing a string more than once.

---

## 💻 Clean & Optimal C++ Solution

```cpp
class Solution {
public:
    pair<int,int> count01(const string &s){
        int zeros = 0, ones = 0;
        for (char c : s){
            if (c == '0') zeros++;
            else ones++;
        }
        return {zeros, ones};
    }

    int findMaxForm(vector<string>& strs, int m, int n) {
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));

        for (auto &s : strs){
            auto [zeros, ones] = count01(s);
            // Traverse backwards to avoid recomputation (like 0/1 knapsack)
            for (int i = m; i >= zeros; i--){
                for (int j = n; j >= ones; j--){
                    dp[i][j] = max(dp[i][j], dp[i - zeros][j - ones] + 1);
                }
            }
        }

        return dp[m][n];
    }
};

```
## ✅ Complexity
Step------------------------------Complexity

Counting 0/1 per string-----------O(len(string))

DP transitions--------------------O(m × n × number of strings)

Space	----------------------------O(m × n)
