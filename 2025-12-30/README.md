# 840. Magic Squares In Grid

## Problem Statement

A **3 x 3 magic square** is a 3 x 3 grid filled with **distinct numbers from 1 to 9** such that:

- Each row has the same sum  
- Each column has the same sum  
- Both diagonals have the same sum  

You are given a `row x col` grid of integers.  
Return the **number of 3 x 3 magic square subgrids** inside the grid.

**Note:**  
- A magic square must contain numbers from `1` to `9` (distinct)  
- The grid itself may contain numbers up to `15`

---

## Example

**Input**

grid = [[4,3,8,4],
[9,5,1,9],
[2,7,6,2]]


**Output**


---

## Solution (C++)

```cpp
class Solution {
public:
    int numMagicSquaresInside(vector<vector<int>>& grid) {
        int ans = 0;
        int rows = grid.size();
        int cols = grid[0].size();

        for (int i = 0; i + 2 < rows; ++i) {
            for (int j = 0; j + 2 < cols; ++j) {
                if (grid[i][j] % 2 == 0 && grid[i + 1][j + 1] == 5) {
                    ans += isMagic(grid, i, j);
                }
            }
        }
        return ans;
    }

private:
    int isMagic(const vector<vector<int>>& grid, int i, int j) {
        string s;
        for (int num : {0, 1, 2, 5, 8, 7, 6, 3}) {
            s += to_string(grid[i + num / 3][j + num % 3]);
        }
        return string("4381672943816729").find(s) != string::npos ||
               string("9276183492761834").find(s) != string::npos;
    }
};

```
