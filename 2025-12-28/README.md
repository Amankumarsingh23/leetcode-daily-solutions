# 1351. Count Negative Numbers in a Sorted Matrix
## 🧠 Key Observation

- The matrix is sorted in non-increasing order:

- Rows: left → right decreasing

- Columns: top → bottom decreasing

- So once you find the first negative in a row, everything to the right is also negative.

## 🚀 Optimal Approach — O(m + n)

Start from the top-right corner and walk smartly.

### Strategy

- If current value is negative:

  - All elements below it in that column are also negative

  - Count them

  - Move left

- Else (value ≥ 0):

  - Move down

## ✅ C++ Solution (Best Possible)
```
class Solution {
public:
    int countNegatives(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int row = 0, col = n - 1;
        int count = 0;

        while (row < m && col >= 0) {
            if (grid[row][col] < 0) {
                count += (m - row);
                col--;
            } else {
                row++;
            }
        }
        return count;
    }
};
```
