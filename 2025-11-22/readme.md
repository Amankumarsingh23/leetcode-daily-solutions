# 🔢 LeetCode 3190 — Find Minimum Operations to Make All Elements Divisible by Three

**Difficulty:** Easy  
**Tags:** Math, Modulo  

---

## 📝 Problem Summary
You are given an integer array `nums`.

In **one** operation, you may **add 1 or subtract 1** from **any** element.

Your goal:

> **Make every element divisible by 3 using the minimum number of operations.**

---

## 💡 Key Insight
For any number `x`, the only thing that matters is:

```
x % 3  →  remainder
```

### Remainder cases:
- `x % 3 == 0` → already divisible → **0 operations**
- `x % 3 == 1` → subtract 1 → **1 operation**
- `x % 3 == 2` → add 1 → **1 operation**

So every non-divisible number needs **exactly 1 operation**.

---

## 🧠 Approach
1. Loop through each number.
2. If it's **not divisible by 3**, add `1` to the operation count.
3. Return total operations.

This works because each element is independent, and fixing each takes at most **one move**.

---

## ⏱️ Complexity
- **Time:** O(n)  
- **Space:** O(1)  

---

## ✅ C++ Solution
```cpp
class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        int ops = 0;
        for (int x : nums) {
            int r = x % 3;
            if (r != 0) ops += 1;   // r == 1 or r == 2 → needs exactly one operation
        }
        return ops;
    }
};
```

---

## 🔍 Example
### Input:
```
[1,2,3,4]
```

### Output:
```
3
```

### Explanation:
- 1 → subtract 1  
- 2 → add 1  
- 4 → subtract 1  

Total = **3 operations**

---
