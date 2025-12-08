# 🔢 LeetCode 1925 — Count Square Sum Triples

**Difficulty:** Easy  
**Tags:** Math, Brute Force, Pythagorean Triple  

---

## 📝 Problem Summary
A **square triple** is a set of integers **(a, b, c)** such that:

```
a² + b² = c²
```

You're given an integer `n`.  
You must count how many such triples satisfy:

```
1 ≤ a, b, c ≤ n
```

Order matters — for example, **(3,4,5)** and **(4,3,5)** are both counted.

---

## 💡 Key Insight
We simply check all pairs `(a, b)` and compute:

```
c² = a² + b²
```

Then check if `c` is:
- an integer (perfect square), and  
- within the range `1…n`.

This is a classic brute-force Pythagorean triple scan.

---

## 🧠 Approach
1. Loop `a` from `1` to `n`.
2. Loop `b` from `1` to `n`.
3. Compute `c² = a*a + b*b`.
4. Check if `c = sqrt(c²)` is an integer and `c ≤ n`.
5. Increase count.

Total complexity: **O(n²)** — fine for given constraints.

---

## ⏱️ Complexity
- **Time:** O(n²)  
- **Space:** O(1)

---

## ✅ C++ Solution
```cpp
class Solution {
public:
    int countTriples(int n) {
        int cnt = 0;
        for (int a = 1; a <= n; a++) {
            for (int b = 1; b <= n; b++) {
                int c2 = a*a + b*b;
                int c = sqrt(c2);
                if (c <= n && c*c == c2) {
                    cnt++;
                }
            }
        }
        return cnt;
    }
};
```

---

## 🔍 Example

### Input:
```
n = 5
```

### Output:
```
2
```

### Explanation:
The valid triples are:
- (3, 4, 5)
- (4, 3, 5)

---
