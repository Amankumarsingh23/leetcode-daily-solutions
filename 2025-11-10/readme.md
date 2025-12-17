# 🟦 3542. Minimum Operations to Convert All Elements to Zero
✔️ **LeetCode — Medium**  
✔️ **Monotonic Stack**  
✔️ **Greedy Layer Removal**

---

## 📌 Problem Summary

You are given an array `nums` of non-negative integers.

### 🔹 Operation
In one operation:
- Select a subarray `[i, j]`
- Find the **minimum non-negative integer** in that subarray
- Set **all occurrences of that minimum value** in the subarray to `0`

### 🎯 Goal
Return the **minimum number of operations** required to make **all elements zero**.

---

## 🧠 Key Insight

Think of the array as **vertical layers**.

- Each **new height increase** starts a **new operation**
- When height decreases, previously started layers end
- Zeros do **not** create new operations

This naturally leads to a **monotonic increasing stack** approach.

---

## 🧩 Strategy (Greedy + Stack)

- Maintain a stack of increasing values
- Traverse the array:
  - Pop larger values when the current number is smaller
  - If the current number starts a new layer → **count one operation**
- Each operation corresponds to **removing one unique layer height**

---

## 💻 C++ Implementation (Clean & Optimal)

```cpp
class Solution {
public:
    int minOperations(vector<int>& nums) {
        stack<int> st;
        int ops = 0;

        for (int num : nums) {
            // Remove completed layers
            while (!st.empty() && st.top() > num) {
                st.pop();
            }

            // Start a new layer
            if (num > 0 && (st.empty() || st.top() < num)) {
                ops++;
                st.push(num);
            }
        }

        return ops;
    }
};
```

---

## 📊 Complexity Analysis

| Metric | Value |
|------|------|
| **Time Complexity** | `O(n)` |
| **Space Complexity** | `O(n)` (stack) |

---

## ✅ Example Walkthrough

**Input**
```
nums = [0, 2]
```

**Process**
- `0` → ignored
- `2` → new layer → `+1 operation`

**Output**
```
1
```

---

## 🔑 Final Takeaway

This problem is a classic **layer-removal greedy problem**, similar to:
- Histogram problems
- Removing blocks
- Minimum operations to flatten structures

Once you see the **layer interpretation**, the solution becomes very clean.

---

