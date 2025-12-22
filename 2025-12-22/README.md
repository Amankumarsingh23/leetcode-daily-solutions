# 960. Delete Columns to Make Sorted III ✅

(This is a DP + LIS on columns problem.)

## 🧠 Key Insight

We want each row individually to be non-decreasing left to right after deletions.

Equivalently:


- We want to keep a subsequence of columns

- Such that for every row, characters are non-decreasing

So this becomes:

Find the longest sequence of columns such that for every row r: 

            strs[r][i] ≤ strs[r][j] 
            for consecutive kept columns i < j

Then:

            answer = total_columns − longest_valid_sequence

## 🚀 Dynamic Programming (LIS on Columns)

Let:

            dp[j] = length of longest valid column sequence ending at column j


Transition:

            dp[j] = 1 + max(dp[i]) for all i < j
            where for every row r:
            strs[r][i] <= strs[r][j]

✅ C++ Solution

            class Solution {
            public:
            int minDeletionSize(vector<string>& strs) {
              int n = strs.size();
             int m = strs[0].size();

        vector<int> dp(m, 1);
        int best = 1;

        for (int j = 0; j < m; j++) {
            for (int i = 0; i < j; i++) {
                bool ok = true;
                for (int r = 0; r < n; r++) {
                    if (strs[r][i] > strs[r][j]) {
                        ok = false;
                        break;
                    }
                }
                if (ok) {
                    dp[j] = max(dp[j], dp[i] + 1);
                }
            }
            best = max(best, dp[j]);
        }

        return m - best;
    }
    };

| Metric | Value         |
| ------ | ------------- |
| Time   | **O(n × m²)** |
| Space  | **O(m)**      |

Constraints allow this.

## 🧪 Example Walkthrough
Input
        ["babca","bbazb"]


Columns:

0: b b
1: a b
2: b a
3: c z
4: a b


Longest valid column subsequence:

    columns [2, 3] → ["bc", "az"]


Length = 2
Total columns = 5

Output
5 - 2 = 3

## ❌ Common Wrong Ideas

- ❌ Greedy column deletion
- ❌ Row-wise sorting
- ❌ Treating like 955 (different condition!)

## 🏆 Pattern Summary
Problem	Technique
- 944	Column check
- 955	Greedy + state
- 960	DP / LIS on columns