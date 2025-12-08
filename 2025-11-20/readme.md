# 🎯 LeetCode 757 — Set Intersection Size At Least Two

**Difficulty:** Hard  
**Tags:** Greedy, Sorting, Intervals  

---

## 📝 Problem Summary
You are given `intervals[i] = [startᵢ, endᵢ]`, representing every integer between **startᵢ and endᵢ** (inclusive).

You must build a set `nums` such that:

> **Every interval contains at least two integers from `nums`**

Your job:

> **Return the minimum size of such a containing set.**

---

## 🔍 Example

### Input:
```
intervals = [[1,3], [3,7], [8,9]]
```

### Output:
```
5
```

A valid minimal set:
```
[2, 3, 4, 8, 9]
```

---

## 💡 Key Idea — Greedy with Smart Sorting
We want to place numbers as **late as possible**, so they cover more intervals.

### Strategy:
1. **Sort intervals** by:
   - Increasing `end`
   - If ties: decreasing `start`
2. Keep track of the **two largest numbers** we placed:  
   - Let them be `a` and `b`, where `a < b`
3. For each interval:
   - If both `a` and `b` already lie inside → do nothing  
   - If only `b` lies inside → add **one number** (`end`)  
   - If none lie inside → add **two numbers** (`end-1` & `end`)

This greedy choice works because picking numbers at the **end boundary** maximizes useful coverage for future intervals.

---

## ⏱️ Complexity
- **Time:** `O(n log n)` (sorting)  
- **Space:** `O(1)` extra

---

## ✅ C++ Solution (Clean & Optimal)
```cpp
class Solution {
public:
    int intersectionSizeTwo(vector<vector<int>>& intervals) {
        // Step 1: sort by end asc, start desc
        sort(intervals.begin(), intervals.end(), [](auto &a, auto &b) {
            if (a[1] == b[1]) return a[0] > b[0];
            return a[1] < b[1];
        });

        int a = -1, b = -1;   // last two chosen numbers
        int count = 0;

        for (auto &in : intervals) {
            int l = in[0], r = in[1];

            bool hasA = (a >= l && a <= r);
            bool hasB = (b >= l && b <= r);

            if (hasA && hasB) {
                // Already has 2 numbers inside
                continue;
            }
            else if (hasB) {
                // Only b is inside → need one more
                a = b;
                b = r;
                count += 1;
            }
            else {
                // None inside → need two new numbers
                a = r - 1;
                b = r;
                count += 2;
            }
        }

        return count;
    }
};
```

---

## 🏁 Final Notes
- Sorting ensures intervals with smaller end limits get satisfied first.  
- Always choosing numbers at `r` and `r-1` maximizes reuse.  
- Pure greedy — no DP required.

---


