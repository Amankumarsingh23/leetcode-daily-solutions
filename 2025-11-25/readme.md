# 🚀 LeetCode 1015 — Smallest Integer Divisible by K

## 📝 Problem Summary
Given a positive integer **k**, find the **length** of the smallest positive integer **n** such that:

- `n` is divisible by `k`
- `n` consists **only of digit '1'**  
  (examples: `1`, `11`, `111`, `1111`, ...)

If no such number exists, return **-1**.

---

## 💡 Key Insight
A number made of only `1`s is called a **repunit**.

Important facts:

- A repunit **cannot** be divisible by numbers containing factor **2** or **5**.  
  Because any number made of only `1`s ends with digit `1`.

Hence:

```
If k % 2 == 0 or k % 5 == 0 → answer is -1.
```

---

## 🧠 Approach

Instead of building the huge repunit (which would overflow), we only track the **remainder**:

```
rem = (rem * 10 + 1) % k
```

We check for at most `k` iterations because remainders repeat (Pigeonhole Principle).

When remainder becomes `0`, we found the length.

---

## ⏱️ Time & Space Complexity

- **Time:** `O(k)`  
- **Space:** `O(1)`

---

## ✅ C++ Solution

```cpp
class Solution {
public:
    int smallestRepunitDivByK(int k) {
        if (k % 2 == 0 || k % 5 == 0) return -1;

        int rem = 0;
        for (int len = 1; len <= k; len++) {
            rem = (rem * 10 + 1) % k;
            if (rem == 0) return len;
        }

        return -1;
    }
};
```

---

## 🎯 Example
**Input:**  
`k = 1`  
**Output:**  
`1`  
Because the smallest repunit divisible by 1 is simply:  
`1`

---


