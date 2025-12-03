# 3625. Count Number of Trapezoids II

**Language:** C++
**Solution file:** `3625_count_number_of_trapezoids_ii.cpp`

---

## 📝 Summary

Given **n distinct points** on a 2D plane, count how many **unique trapezoids** (convex quadrilaterals with **≥ 1 pair of parallel sides**) can be formed.

**Constraints:**

* 4 ≤ n ≤ 500
* Coordinates ∈ [-1000, 1000]

---

## 💡 Intuition

A trapezoid has **at least one pair of parallel sides**.
A line segment is defined by two points → two parallel sides → two pairs of points.

So the problem becomes:

* Count **all pairs of parallel lines** (formed by point pairs)
* But **subtract parallelograms**, because they are counted incorrectly when both pairs of sides are parallel.

---

## 🧠 Approaches

### **1. Brute Force (Impractical)**

Check every 4-point combination, compute slopes of all 6 edges, verify trapezoid shape.

* **Time:** O(n⁴) → impossible for n=500
* **Space:** O(1)

---

### **2. Optimized: Slope + Intercept + Midpoint (Correct & Efficient)**

This is the required method.

#### **Step 1 — Process all point pairs**

For every pair (i, j) compute:

* **Slope** = dy/dx as a reduced fraction
* **Intercept** = b from line equation y = mx + b
* For vertical lines → slope = 1/0, intercept = x

Store:

* `slope → list of intercepts`
* `midpoint → list of slopes` (for parallelogram detection)

#### **Step 2 — Count parallel line pairs**

For each slope group:

* Suppose there are `m` segments
* Total unordered pairs: `m * (m - 1) / 2`
* But if two segments share **same intercept**, they lie on the same infinite line → invalid

  * subtract `(count * (count - 1)) / 2` for each repeated intercept

This gives **all unique trapezoid candidates** (includes parallelograms).

---

### **Step 3 — Subtract parallelograms**

Parallelograms have diagonals with the **same midpoint**.

For each midpoint, group diagonals by slope and:

* Subtract pairs of diagonals with *different slopes*
* Each parallelogram was counted twice → subtract accordingly

---

## ⭐ Why Fractions?

To avoid floating-point issues, slopes/intercepts must be stored as **normalized integer fractions**:

* Reduce numerator/denominator by GCD
* Ensure denominator > 0
* Vertical lines use `(1/0)` marker

---

## ⏳ Complexity

* **Time:** O(n² log n)
* **Space:** O(n²)
  Both are acceptable for n ≤ 500.

---

## 🧾 Code (C++)


#include <bits/stdc++.h>
using namespace std;

// Fraction representing num/den in normalized form.
// Use den == 0 to represent infinity (vertical lines).
struct Fraction {
    long long num;
    long long den;
    Fraction(long long n = 0, long long d = 1) : num(n), den(d) {
        normalize();
    }
private:
    static long long absll(long long x) { return x < 0 ? -x : x; }
    static long long gcdll(long long a, long long b) {
        if (a < 0) a = -a;
        if (b < 0) b = -b;
        while (b) {
            long long t = a % b;
            a = b;
            b = t;
        }
        return a < 0 ? -a : a;
    }
    void normalize() {
        if (den == 0) {
            // Represent infinity; set num to 1 as a canonical marker
            num = 1;
            den = 0;
            return;
        }
        if (den < 0) {
            num = -num;
            den = -den;
        }
        long long g = gcdll(absll(num), absll(den));
        if (g == 0) g = 1;
        num /= g;
        den /= g;
    }
public:
    bool operator==(const Fraction &o) const {
        return num == o.num && den == o.den;
    }
    // Provide ordering if ever needed (not required for unordered_map).
    bool operator<(const Fraction &o) const {
        // Handle infinities
        if (den == 0 && o.den == 0) return false;
        if (den == 0) return true;   // treat inf as "larger" or consistent ordering
        if (o.den == 0) return false;
        // compare num/den < o.num/o.den
        return num * o.den < o.num * den;
    }
};

// Hash + equal for unordered_map keys
struct FractionHash {
    size_t operator()(Fraction const &f) const noexcept {
        // combine num and den hashes
        return std::hash<long long>()(f.num) ^ (std::hash<long long>()(f.den) << 1);
    }
};
struct FractionEq {
    bool operator()(Fraction const &a, Fraction const &b) const noexcept {
        return a.num == b.num && a.den == b.den;
    }
};

class Solution {
public:
    int countTrapezoids(vector<vector<int>>& points) {
        int n = (int)points.size();
        if (n < 4) return 0;

        // slope -> list of intercepts for all pairs that produce that slope
        unordered_map<Fraction, vector<Fraction>, FractionHash, FractionEq> slope_to_intercepts;
        // midpoint (x1+x2, y1+y2) -> list of slopes (for parallelogram detection)
        map<pair<long long,long long>, vector<Fraction>> midpoint_to_slopes;

        for (int i = 0; i < n; ++i) {
            long long x1 = points[i][0], y1 = points[i][1];
            for (int j = i + 1; j < n; ++j) {
                long long x2 = points[j][0], y2 = points[j][1];
                long long dx = x2 - x1;
                long long dy = y2 - y1;

                Fraction slope, intercept;
                if (dx == 0) {
                    // vertical line: slope = inf, intercept store x (as fraction)
                    slope = Fraction(1, 0);
                    intercept = Fraction(x1, 1);
                } else {
                    slope = Fraction(dy, dx); // normalized dy/dx
                    // intercept b = y - m*x = (y*dx - dy*x)/dx
                    long long num = y1 * dx - dy * x1;
                    long long den = dx;
                    intercept = Fraction(num, den);
                }

                slope_to_intercepts[slope].push_back(intercept);

                // Use (x1+x2, y1+y2) as midpoint key multiplied by 2 (avoid fractions)
                midpoint_to_slopes[{x1 + x2, y1 + y2}].push_back(slope);
            }
        }

        long long result = 0;

        // Count trapezoid candidates: for each slope, choose two distinct lines (different intercepts)
        for (auto &entry : slope_to_intercepts) {
            auto &intercepts = entry.second;
            int m = (int)intercepts.size();
            if (m < 2) continue;

            // Count total unordered pairs of these lines
            long long total_pairs = 1LL * m * (m - 1) / 2;

            // Subtract pairs that are actually on the same infinite line (same intercept)
            unordered_map<Fraction, int, FractionHash, FractionEq> cnt;
            for (auto &b : intercepts) cnt[b]++;

            long long same_intercept_pairs = 0;
            for (auto &p : cnt) {
                int c = p.second;
                if (c > 1) same_intercept_pairs += 1LL * c * (c - 1) / 2;
            }

            result += (total_pairs - same_intercept_pairs);
        }

        // Subtract parallelograms counted above.
        // For each midpoint, count pairs of diagonals with different slopes (these correspond to parallelograms).
        for (auto &entry : midpoint_to_slopes) {
            auto &slopes = entry.second;
            if (slopes.size() < 2) continue;

            unordered_map<Fraction, int, FractionHash, FractionEq> cnt;
            for (auto &s : slopes) cnt[s]++;

            // For slopes at same midpoint, subtract pairs across different slopes.
            // Do it incrementally to avoid double counting: subtract acc * count for each slope group.
            long long acc = 0;
            for (auto &p : cnt) {
                int c = p.second;
                result -= acc * c;
                acc += c;
            }
        }

        return (int)result;
    }
};

// For local testing (uncomment to run locally).
/*
int main() {
    Solution sol;
    vector<vector<int>> pts1 = {{-3,2},{3,0},{2,3},{3,2},{2,-3}};
    cout << sol.countTrapezoids(pts1) << "\n"; // expected 2

    vector<vector<int>> pts2 = {{0,0},{1,0},{0,1},{2,1}};
    cout << sol.countTrapezoids(pts2) << "\n"; // expected 1
    return 0;
}
*/




---

## 📌 Final Notes

* Always normalize slopes and intercepts.
* Handle vertical lines specially.
* Parallelogram subtraction is essential for correctness.
* Use long long to avoid overflow.
