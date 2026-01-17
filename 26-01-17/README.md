# 3047. Find the Largest Area of Square Inside Two Rectangles

## Problem Statement

You are given `n` rectangles on a 2D plane, each aligned with the x and y axes.

- `bottomLeft[i] = [ai, bi]` represents the bottom-left corner of the `i`th rectangle
- `topRight[i] = [ci, di]` represents the top-right corner of the `i`th rectangle

Your task is to find the **maximum area of a square** that can fit **inside the intersecting region of at least two rectangles**.

If no such square exists, return `0`.

---

## Key Observations

1. A square can only exist inside the **intersection** of two rectangles.
2. We only need to consider **pairs of rectangles**.
3. For any two rectangles:
   - Compute their intersection rectangle.
   - The largest square inside that intersection has side length:
     ```
     min(intersection width, intersection height)
     ```
4. The required answer is the **maximum square area** among all rectangle pairs.

---
x1 = max(ai, aj)
y1 = max(bi, bj)


- Top-right of intersection:
x2 = min(ci, cj)
y2 = min(di, dj)
## Intersection of Two Rectangles

For rectangles `i` and `j`:



- Width  = `x2 - x1`
- Height = `y2 - y1`

If either width or height is non-positive, the rectangles do not overlap.

---

## Algorithm

1. Iterate over all pairs of rectangles.
2. Compute intersection width and height.
3. If intersection exists:
 - Side length = `min(width, height)`
 - Area = `side * side`
4. Track the maximum area.
5. Return the result.

---

## C++ Solution

```cpp
class Solution {
public:
  long long largestSquareArea(vector<vector<int>>& bottomLeft,
                              vector<vector<int>>& topRight) {
      int n = bottomLeft.size();
      long long ans = 0;

      for (int i = 0; i < n; i++) {
          for (int j = i + 1; j < n; j++) {
              int x1 = max(bottomLeft[i][0], bottomLeft[j][0]);
              int y1 = max(bottomLeft[i][1], bottomLeft[j][1]);
              int x2 = min(topRight[i][0], topRight[j][0]);
              int y2 = min(topRight[i][1], topRight[j][1]);

              int width  = x2 - x1;
              int height = y2 - y1;

              if (width > 0 && height > 0) {
                  long long side = min(width, height);
                  ans = max(ans, side * side);
              }
          }
      }
      return ans;
  }
};

```
- Bottom-left of intersection:
