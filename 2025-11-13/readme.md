# 🟦 3228. Maximum Number of Operations to Move Ones to the End  
**LeetCode — Medium | Greedy | Counting | String**

---

## 📌 Problem Summary

You are given a **binary string** `s`.

You may perform the following operation any number of times:

- Choose an index `i` where  
  `s[i] == '1'` **and** `s[i+1] == '0'`
- Move this `'1'` to the **right** until it:
  - reaches the **end**, or  
  - reaches the **next `'1'`**

This **entire movement counts as ONE operation**.

Return the **maximum number of operations** possible.

---

## 🧠 Key Insight

When does an operation happen?

✔ A `'1'` contributes an operation whenever it can move over a `'0'`  
✔ A `'0'` triggers operations for **all previous `'1'`s**, **only when**:
  - it is the **last character**, or
  - it is **followed by `'1'`**

Why?

Because these zero-block segments are exactly where all accumulated `'1'`s will “slide” to the right.

---

## 🔥 Core Logic

- Let `ones` = number of `'1'`s seen so far while scanning left → right.
- When you encounter a `'0'` that is:
  - the **last character**, or  
  - the next char is `'1'`  
  → This `'0'` is the **end of a 0-segment**, and all previous `'1'`s can perform an operation.

So for such a zero:
   operations += ones
   
This is exactly what the optimal greedy solution does.

---

## 💻 C++ Code (Clean & Correct)

```cpp
class Solution {
public:
    int maxOperations(string s) {
        int ans = 0;
        int ones = 0;
        int n = s.size();

        for (int i = 0; i < n; ++i) {
            if (s[i] == '1') {
                ones++;
            } else { // s[i] == '0'
                // zero at boundary of segment → triggers operations
                if (i == n - 1 || s[i + 1] == '1') {
                    ans += ones;
                }
            }
        }

        return ans;
    }
};


```
## ✅ Complexity


    Category	Value
    Time	O(n)
    Space	O(1)
    Strategy	Greedy + Counting

