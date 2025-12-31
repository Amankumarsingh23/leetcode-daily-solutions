# 1970. Last Day Where You Can Still Cross

This is a Hard problem, but it has a very clean idea once you see it.

## 🔑 Key Insight

Instead of simulating day by day forward (which is too slow), we:

## 👉 Binary Search on the answer (day)

For a given day d:

- Flood the first d cells

- Check if there exists a path from top to bottom using only land (0)

- Use BFS / DFS

This works because:

- If you can cross on day d, then you can cross on all earlier days

- If you cannot cross on day d, then you cannot cross on any later day

### 👉 Monotonic property → Binary Search

## 🧠 Algorithm

1. Binary search day in range [0, row * col]

2. For mid day:

  - Build grid where first mid flooded cells are water

  - BFS from all land cells in top row

  - If any BFS reaches bottom row → crossing possible

3. Store the last valid day

## ⏱ Complexity
| Part          | Complexity            |
| ------------- | --------------------- |
| Binary Search | `O(log(R*C))`         |
| BFS per check | `O(R*C)`              |
| Total         | **O(R*C log(R*C))** ✅ |

## ✅ C++ Solution (Accepted)
```
class Solution {
public:
    int row, col;
    vector<vector<int>> dirs = {{1,0},{-1,0},{0,1},{0,-1}};

    bool canCross(int day, vector<vector<int>>& cells) {
        vector<vector<int>> grid(row, vector<int>(col, 0));

        // Flood first 'day' cells
        for (int i = 0; i < day; i++) {
            int r = cells[i][0] - 1;
            int c = cells[i][1] - 1;
            grid[r][c] = 1;
        }

        queue<pair<int,int>> q;
        vector<vector<bool>> vis(row, vector<bool>(col, false));

        // Start BFS from top row
        for (int c = 0; c < col; c++) {
            if (grid[0][c] == 0) {
                q.push({0, c});
                vis[0][c] = true;
            }
        }

        while (!q.empty()) {
            auto [r, c] = q.front(); q.pop();

            if (r == row - 1) return true;

            for (auto &d : dirs) {
                int nr = r + d[0];
                int nc = c + d[1];
                if (nr >= 0 && nr < row && nc >= 0 && nc < col &&
                    !vis[nr][nc] && grid[nr][nc] == 0) {
                    vis[nr][nc] = true;
                    q.push({nr, nc});
                }
            }
        }
        return false;
    }

    int latestDayToCross(int r, int c, vector<vector<int>>& cells) {
        row = r;
        col = c;

        int low = 0, high = cells.size(), ans = 0;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (canCross(mid, cells)) {
                ans = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return ans;
    }
};
```


## 🔥 Why this is optimal

- Avoids simulation

- Uses graph connectivity

- Very common Google / Amazon / Meta style problem

