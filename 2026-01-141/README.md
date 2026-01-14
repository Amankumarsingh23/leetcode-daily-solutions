# Separate Squares — Equal Area Horizontal Split (Overlaps Counted Once)

## Problem Statement

You are given a 2D integer array `squares`, where each  
`squares[i] = [xi, yi, li]` represents a square with:

- Bottom-left corner at `(xi, yi)`
- Side length `li`
- Edges parallel to the x-axis

Your task is to find the **minimum y-coordinate** of a horizontal line such that:

- The **total area covered by squares above the line**
- Is **equal** to the **total area covered by squares below the line**

### Important Notes

- Squares **may overlap**
- **Overlapping regions are counted only once**
- Answers within **1e-5** of the correct value are accepted

---

## Example

**Input**

squares = [[0,0,1],[2,2,1]]


**Output**

1.00000


**Explanation**

Any horizontal line between `y = 1` and `y = 2` splits the total covered area equally.  
The minimum valid y-coordinate is `1.0`.

---

## Core Insight

This is a **2D union-area problem**, not a simple sum of individual squares.

Because overlaps must be counted only once, we cannot compute areas independently.
Instead, we use a **sweep line along the y-axis** combined with a **segment tree on the x-axis** to compute the **exact union area**.

The idea is:

1. Compute the **total union area** of all squares.
2. Sweep again from bottom to top and **accumulate area**.
3. Stop at the exact y-coordinate where accumulated area becomes **half of the total**.

This guarantees the **minimum possible y** satisfying the condition.

---

## Algorithm Explanation

### 1. Sweep Line Events

Each square contributes two events:
- Enter event at `y`
- Exit event at `y + l`

Each event carries an x-interval `[x, x + l)`.

---

### 2. Coordinate Compression (X-axis)

We collect all unique x-coordinates from square edges and compress them.
This allows us to efficiently track covered x-length using a segment tree.

---

### 3. Segment Tree Meaning

- `cnt[node]` → number of active intervals covering the segment
- `seg[node]` → total covered x-length for that segment

If `cnt > 0`, the entire segment is covered.

---

### 4. Total Area Calculation

While sweeping:

area += covered_x_length * (next_y - current_y)


This computes the **exact union area**.

---

### 5. Finding the Split Line

We sweep again and keep accumulating area.
When cumulative area reaches `total_area / 2`, the answer lies **within that y-interval**.

The exact y is:

y = current_y + (remaining_area / covered_x_length)


---

## C++ Implementation

```cpp
class Solution {
public:
    struct Event {
        double y;
        int type;          // +1 entering, -1 leaving
        double x1, x2;
    };

    vector<double> xs;
    vector<int> cnt;
    vector<double> seg;

    void update(int idx, int l, int r, int ql, int qr, int val) {
        if (qr <= l || r <= ql) return;

        if (ql <= l && r <= qr) {
            cnt[idx] += val;
        } else {
            int m = (l + r) / 2;
            update(idx * 2, l, m, ql, qr, val);
            update(idx * 2 + 1, m, r, ql, qr, val);
        }

        if (cnt[idx] > 0) {
            seg[idx] = xs[r] - xs[l];
        } else {
            seg[idx] = (l + 1 == r) ? 0 : seg[idx * 2] + seg[idx * 2 + 1];
        }
    }

    double separateSquares(vector<vector<int>>& squares) {
        vector<Event> events;

        for (auto &s : squares) {
            double x = s[0], y = s[1], l = s[2];
            events.push_back({y, +1, x, x + l});
            events.push_back({y + l, -1, x, x + l});
            xs.push_back(x);
            xs.push_back(x + l);
        }

        sort(xs.begin(), xs.end());
        xs.erase(unique(xs.begin(), xs.end()), xs.end());

        sort(events.begin(), events.end(),
             [](const Event& a, const Event& b) {
                 return a.y < b.y;
             });

        int m = xs.size();
        cnt.assign(4 * m, 0);
        seg.assign(4 * m, 0);

        auto getX = [&](double x) {
            return lower_bound(xs.begin(), xs.end(), x) - xs.begin();
        };

        // First sweep: total union area
        double total = 0.0;
        for (int i = 0; i + 1 < events.size(); i++) {
            int l = getX(events[i].x1);
            int r = getX(events[i].x2);
            update(1, 0, m - 1, l, r, events[i].type);

            double dy = events[i + 1].y - events[i].y;
            total += seg[1] * dy;
        }

        double target = total / 2.0;

        // Reset for second sweep
        cnt.assign(4 * m, 0);
        seg.assign(4 * m, 0);

        double cur = 0.0;
        for (int i = 0; i + 1 < events.size(); i++) {
            int l = getX(events[i].x1);
            int r = getX(events[i].x2);
            update(1, 0, m - 1, l, r, events[i].type);

            double dy = events[i + 1].y - events[i].y;
            double add = seg[1] * dy;

            if (cur + add >= target) {
                return events[i].y + (target - cur) / seg[1];
            }
            cur += add;
        }

        return 0.0;
    }
};




