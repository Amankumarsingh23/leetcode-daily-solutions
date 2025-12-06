# 🧮 LeetCode 3512 — Minimum Operations to Make Array Sum Divisible by K

**Difficulty:** Easy  
**Tags:** Math, Modular Arithmetic  

---

## 📝 Problem Summary
You are given:
- An integer array **nums**
- An integer **k**

You may perform the following operation any number of times:

> Select an index `i` and replace `nums[i]` with `nums[i] - 1`.

Your task:

> Return the **minimum number of operations** required to make  
> the **sum of the array divisible by k**.

---

## 💡 Intuition
Each operation reduces the total sum by **exactly 1**.

Let:
sum = total sum of nums
r = sum % k

To make `sum` divisible by `k`, you need to reduce `sum` until:

(sum - ops) % k == 0

This is true exactly when:  ops = r


So the number of operations needed is simply:
> **The remainder of sum modulo k**

---

## 🧠 Complexity
- **Time:** O(n) – computing the sum  
- **Space:** O(1)

---

## ✅ C++ Code (Very Simple)
```cpp
class Solution {
public:
    int minOperations(vector<int>& nums, int k) {
        long long sum = 0;
        for(int x : nums) {
            sum += x;
        }
        return sum % k;  // number of decrements needed
    }
};

````
Final Notes

Only subtraction operations allowed → only sum matters.

No need to modify or simulate array values.

Clean O(n) solution.


