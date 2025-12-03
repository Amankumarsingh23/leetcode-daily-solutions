# 3623. Count Number of Trapezoids I

**Language:** C++
**Solution file:** `3623_count_number_of_trapezoids_i.cpp`

---

## 📝 Summary

We are given **n points** on a 2D plane.
A **horizontal trapezoid** is a convex quadrilateral with **at least one pair of horizontal sides** — sides parallel to the **x-axis**, meaning both endpoints share the **same y-coordinate**.

We must count how many **unique horizontal trapezoids** can be formed using **any 4 distinct points**, modulo **10⁹+7**.

---

## 💡 Intuition

A horizontal trapezoid needs **two horizontal segments on different y-levels**.

A horizontal segment is formed by picking **any 2 points with the same y**.

So the problem transforms into:

1. Group all points by **y-coordinate**.
2. For each group with size `k`, number of horizontal segments = **C(k, 2)**.
3. Let these segment counts be:

   ```
   A₁, A₂, A₃, ...
   ```
4. We need to count **all unordered pairs of horizontal segments on different y-levels**:
   → Aᵢ × Aⱼ for all i ≠ j.

This equals:

[
\frac{(\sum A_i)^2 - \sum (A_i^2)}{2}
]

This avoids double counting.

---

## 🧠 Approach

### **Step 1 — Count points per y-level**

Use a hash map:
`y → count_of_points_on_that_y`.

### **Step 2 — Compute segments on each y-level**

For each y with count = k:
`A = C(k,2) = k * (k - 1) / 2`.

### **Step 3 — Apply the formula**

[
\text{answer} = \frac{( \sum A )^2 - \sum(A^2)}{2}
]

Handle modulo carefully.

### Why this works

A horizontal trapezoid is uniquely defined by:

* choosing 1 horizontal segment from y₁
* choosing 1 horizontal segment from y₂
* making sure y₁ ≠ y₂

This is exactly what the formula counts.

---

## ⏳ Complexity

* **Time:** O(n)
* **Space:** O(n)
  Perfectly efficient.

---

## 🧾 Code (C++)

Paste this into `3623_count_number_of_trapezoids_i.cpp`:

```cpp
class Solution { 
public:
    static const long long MOD = 1e9 + 7;

    long long C2(long long x) {
        if (x < 2) return 0;
        return (x * (x - 1) / 2) % MOD;
    }

    int countTrapezoids(vector<vector<int>>& points) {
        unordered_map<int, long long> freq;

        // Count points for each y
        for (auto &p : points) {
            freq[p[1]]++;
        }

        long long sumA = 0, sumA2 = 0;

        // Compute A_i and accumulate sums
        for (auto &it : freq) {
            long long A = C2(it.second);
            sumA = (sumA + A) % MOD;
            sumA2 = (sumA2 + (A * A) % MOD) % MOD;
        }

        // Formula: (sumA^2 - sumA2) / 2
        long long ans = ( (sumA * sumA) % MOD - sumA2 + MOD ) % MOD;

        // Multiply by modular inverse of 2
        long long inv2 = 500000004; // (2^(-1) mod 1e9+7)
        ans = (ans * inv2) % MOD;

        return ans;
    }
};
```

---

## 📌 Final Notes

* The trick is reducing the geometry problem to **segment counting**.
* No slope checking is required because only **horizontal** segments matter.
* The final formula avoids O(n²) or O(n⁴) brute force.
