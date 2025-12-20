## 944. Delete Columns to Make Sorted

**Difficulty:** Easy  
**Topic:** Strings  

### Problem Statement

You are given an array of strings `strs`, where all strings have the same length.

The strings form a grid when written one per line.  
A column is considered **sorted** if the characters in that column are in non-decreasing lexicographical order from top to bottom.

Return the number of columns that are **not sorted** and must be deleted.

---

### Approach

- Let `n` be the number of strings and `m` be the length of each string.
- For each column:
  - Compare characters row by row.
  - If any character is smaller than the one above it, the column is unsorted.
  - Increment the deletion count and move to the next column.

---

### Time and Space Complexity

- **Time Complexity:** `O(n * m)`
- **Space Complexity:** `O(1)`

---

### C++ Solution

```cpp
class Solution {
public:
    int minDeletionSize(vector<string>& strs) {
        int n = strs.size();
        int m = strs[0].size();
        int deletions = 0;

        for (int col = 0; col < m; col++) {
            for (int row = 1; row < n; row++) {
                if (strs[row][col] < strs[row - 1][col]) {
                    deletions++;
                    break;
                }
            }
        }
        return deletions;
    }
};
```
