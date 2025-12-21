# 955. Delete Columns to Make Sorted II ✅

  (This is trickier than 944 and many wrong greedy ideas fail.)

## 🧠 Key Insight (Very Important)

    We do NOT need each column sorted individually.

    Instead, we need:

    final               
                    strs[0] <= strs[1] <= ... <= strs[n-1]


    So we:


    - Process columns left to right

    - Track which adjacent string pairs are already confirmed sorted

    - Only delete a column if it breaks lexicographic order for any unresolved pair

## 🚀 Greedy Strategy

- Maintain an array sorted[i]:

- sorted[i] = true means strs[i] < strs[i+1] is already guaranteed

- For each column:

    - Check if keeping this column causes any violation

    - If yes → delete column

    - Otherwise → use this column to mark some pairs as sorted

## ✅ C++ Solution

            class Solution {
            public:
            int minDeletionSize(vector<string>& strs) {
            int n = strs.size();
            int m = strs[0].size();
            int deletions = 0;

        vector<bool> sorted(n - 1, false);

        for (int col = 0; col < m; col++) {
            bool bad = false;

            // check if this column causes a violation
            for (int i = 0; i < n - 1; i++) {
                if (!sorted[i] && strs[i][col] > strs[i + 1][col]) {
                    bad = true;
                    break;
                }
            }

            if (bad) {
                deletions++;
                continue; // skip this column
            }

            // update sorted pairs
            for (int i = 0; i < n - 1; i++) {
                if (!sorted[i] && strs[i][col] < strs[i + 1][col]) {
                    sorted[i] = true;
                }
            }
        }

        return deletions;
          }
        };

## ⏱ Complexity

| Metric | Value        |
| ------ | ------------ |
| Time   | **O(n × m)** |
| Space  | **O(n)**     |



## 🧪 Example Walkthrough
    Input
["ca","bb","ac"]

    Process

    - Column 0 → c > b ❌ → delete

    - Column 1 → a < b < c ✔ → valid

    Output
        1

## ❌ Common Mistake

- ❌ Checking each column independently
- ❌ Sorting rows
- ❌ DP (unnecessary)

This problem is greedy + state tracking.

## 🏆 Pattern to Remember

- Lexicographic order stabilization

- Similar problems:

- String ordering with deletions

- Prefix comparison optimization