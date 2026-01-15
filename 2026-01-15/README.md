# 🟦 2943. Maximize Area of Square Hole in Grid

**Difficulty:** Medium  
**Topics:** Arrays, Sorting, Greedy  

---

## 📌 Problem Statement

You are given two integers `n` and `m`, and two integer arrays `hBars` and `vBars`.

- The grid has `n + 2` horizontal bars and `m + 2` vertical bars.
- These bars form `1 × 1` unit cells.
- Bars are indexed starting from `1`.

You can remove:
- Some bars from `hBars` (horizontal bars)
- Some bars from `vBars` (vertical bars)

All other bars are fixed and cannot be removed.

---

### 🎯 Objective

Return the **maximum area** of a **square-shaped hole** that can be formed after removing some bars (possibly none).

---

## 💡 Key Insight

- Removing **consecutive horizontal bars** increases the **height** of the hole.
- Removing **consecutive vertical bars** increases the **width** of the hole.
- If `k` consecutive bars are removed, the resulting hole size becomes `k + 1`.
- A square is limited by the **minimum** of height and width.

\[
\text{Area} = (\min(\text{height}, \text{width}))^2
\]

---

## 🧠 Approach

1. Sort the removable bars.
2. Find the **longest consecutive sequence** in `hBars` → max height.
3. Find the **longest consecutive sequence** in `vBars` → max width.
4. The square side length is the minimum of the two.
5. Return the square of the side length.

---

## ✅ C++ Implementation

```cpp
class Solution {
public:
    int maximizeSquareHoleArea(int n, int m, vector<int>& hBars, vector<int>& vBars) {

        // Helper function to find longest consecutive sequence
        auto maxConsecutive = [](vector<int>& bars) {
            if (bars.empty()) return 1;

            sort(bars.begin(), bars.end());

            int maxLen = 1, currLen = 1;

            for (int i = 1; i < bars.size(); i++) {
                if (bars[i] == bars[i - 1] + 1) {
                    currLen++;
                } else {
                    currLen = 1;
                }
                maxLen = max(maxLen, currLen);
            }

            // Removing k bars creates k + 1 cells
            return maxLen + 1;
        };

        int maxHeight = maxConsecutive(hBars);
        int maxWidth  = maxConsecutive(vBars);

        int side = min(maxHeight, maxWidth);
        return side * side;
    }
};
