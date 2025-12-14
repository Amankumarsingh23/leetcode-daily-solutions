# 🟥 2147. Number of Ways to Divide a Long Corridor  
**LeetCode — Hard | Combinatorics | Greedy Counting**

---

## 📌 Problem Summary

You are given a corridor represented as a string `corridor` of length `n`:

- `'S'` → Seat  
- `'P'` → Plant  

There is already:
- One divider **before index 0**
- One divider **after index n − 1**

You may optionally place **at most one divider** between any two adjacent indices.

---

## 🎯 Objective

Divide the corridor into **non-overlapping sections** such that:

- **Each section contains exactly 2 seats**
- It may contain **any number of plants**
- Sections must be contiguous

Two divisions are considered **different** if at least one divider position differs.

Return the **number of valid ways** to divide the corridor, modulo:
  10^9 + 7


If no valid division exists, return `0`.

---

## 🧠 Key Observations

### ✔️ Total Seats Must Be Even
- Each section needs **exactly 2 seats**
- If total `'S'` count is `0` or odd → **impossible**

---

### ✔️ Divider Choices Come from Plants Between Seat Pairs
Once we complete a section with **2 seats**, the next section must start **after placing a divider**.

If there are `k` plants between two consecutive seat-pairs, then:
  Possible divider positions = k + 1


Each such gap **multiplies** the total number of valid ways.

---

## 🧩 Strategy (Greedy + Counting)

- Traverse the corridor from left to right
- Count seats
- After completing a **pair of seats**, start counting plants
- When a new section begins:
  - Multiply answer by `(plants + 1)`
  - Reset plant counter

---

## 💻 C++ Solution (Optimized & Elegant)

```cpp
class Solution {
public:
    static const int MOD = 1e9 + 7;

    int numberOfWays(string corridor) {
        long long ans = 1;
        int seatCount = 0;
        int plantCount = 0;
        bool countingPlants = false;

        for (char c : corridor) {
            if (c == 'S') {
                seatCount++;

                if (seatCount % 2 == 0) {
                    // Completed a section of exactly 2 seats
                    countingPlants = true;
                } 
                else if (seatCount > 1) {
                    // Starting a new section
                    ans = (ans * (plantCount + 1)) % MOD;
                    plantCount = 0;
                    countingPlants = false;
                }
            } 
            else if (c == 'P' && countingPlants) {
                plantCount++;
            }
        }

        // Invalid if no seats or odd number of seats
        if (seatCount == 0 || seatCount % 2 != 0) return 0;

        return ans;
    }
};
```
| Metric | Value    |
| ------ | -------- |
| Time   | **O(n)** |
| Space  | **O(1)** |

## 📝 Final Notes

- This is a classic combinatorics × greedy problem

- No DP required

- Clean single-pass solution

- Important interview takeaway:

- Count choices between mandatory constraints





