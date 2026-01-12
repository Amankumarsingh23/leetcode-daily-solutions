# LeetCode 1266 — Minimum Time Visiting All Points

**Difficulty:** Easy  
**Topic:** Geometry, Simulation

---

## Problem Summary

You are given `n` points on a 2D plane in a fixed order.  
Each point is represented as `points[i] = [xi, yi]`.

You must visit all points **in the given order**.

In **1 second**, you can:
- Move 1 unit vertically, or
- Move 1 unit horizontally, or
- Move 1 unit vertically and 1 unit horizontally together (diagonal move)

Passing through other points is allowed but does not count as a visit.

Return the **minimum time in seconds** to visit all points.

---

## Key Insight

To move from point  
`A(x1, y1)` to `B(x2, y2)`:
```
dx = |x2 - x1|
dy = |y2 - y1|
```

A diagonal move reduces **both dx and dy by 1 in one second**.

So:
- Use diagonal moves for `min(dx, dy)`
- Use straight moves for the remaining distance

Therefore, the minimum time required is:

time = max(dx, dy)


This is also known as the **Chebyshev distance**.

---

## Strategy

1. Iterate through consecutive pairs of points.
2. For each pair, compute `dx` and `dy`.
3. Add `max(dx, dy)` to the total time.
4. Return the total.

---

## C++ Solution

```cpp
class Solution {
public:
    int minTimeToVisitAllPoints(vector<vector<int>>& points) {
        int totalTime = 0;

        for (int i = 1; i < points.size(); i++) {
            int dx = abs(points[i][0] - points[i - 1][0]);
            int dy = abs(points[i][1] - points[i - 1][1]);
            totalTime += max(dx, dy);
        }

        return totalTime;
    }
};
