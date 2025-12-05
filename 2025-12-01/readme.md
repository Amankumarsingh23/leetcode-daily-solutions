# 🚀 LeetCode 2141 — Maximum Running Time of N Computers  
**Difficulty:** Hard  
**Tag:** Binary Search, Greedy

---

## 📘 Problem Summary  
You have **n computers**, and each computer can hold **one battery at a time**.  
Every battery has a fixed running time (no recharging).

You are allowed to **swap batteries freely at any integer time** (swapping takes 0 time).

Your goal is to determine the **maximum number of minutes** you can run **all n computers simultaneously**.

---

## 🧠 Intuition  

Think of it this way:

- If we want all `n` computers to run for `T` minutes, we need a total of  
  **`T × n` minutes** of battery energy.
- Each battery `b` can contribute at most `min(b, T)` minutes.
- So we sum up contributions from all batteries and check if the total is enough to sustain time `T`.

This naturally becomes a **binary search on T**, because:

- If we CAN run all computers for T minutes,  
  ➝ we might be able to run for a longer time.
- If we CANNOT run for T minutes,  
  ➝ we must try a smaller time.

---

## 🔍 Approach

1. **Binary Search on T**  
   - Minimum possible time = `0`  
   - Maximum possible time = `sum(batteries)` (if all used as one)

2. **Check Function (`canRun`)**
   - Calculate:  
     `total = Σ min(battery[i], T)`  
   - If `total >= T × n`, it's possible.

3. **Return the largest valid T**

This solution is optimal and follows a classic battery distribution trick.

---

## ⏱️ Time & Space Complexity

| Component     | Complexity |
|---------------|------------|
| Binary Search | `O(log(sum(batteries)))` |
| Feasibility Check | `O(m)` where `m = batteries.size()` |
| **Total** | `O(m log(totalPower))` |
| Space | `O(1)` |

---

## ✅ C++ Implementation

```cpp
class Solution {
public:
    long long maxRunTime(int n, vector<int>& batteries) {
        long long left = 0, right = 0;
        
        // Upper bound = total energy available
        for (long long b : batteries) 
            right += b;

        long long ans = 0;
        
        while (left <= right) {
            long long mid = (left + right) / 2;  // Guess: Can all run for mid minutes?
            
            if (canRun(mid, n, batteries)) {
                ans = mid;          // mid is possible, try longer
                left = mid + 1;
            } else {
                right = mid - 1;    // mid impossible, shorten the time
            }
        }
        return ans;
    }

    bool canRun(long long T, int n, vector<int>& batteries) {
        long long total = 0;

        // Each battery contributes min(b, T)
        for (long long b : batteries)
            total += min(b, T);

        // Need total energy >= n*T
        return total >= T * n;
    }
};



📝 Additional Notes

The trick is to realize you don’t need to simulate swapping.

The min(battery, T) idea is the heart of the solution.

This is one of the cleanest binary search + feasibility check patterns in LeetCode Hard problems.
