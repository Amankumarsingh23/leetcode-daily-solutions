# LeetCode 1975 — Maximum Matrix Sum

**Difficulty:** Medium  
**Topic:** Greedy, Math

## Problem

You are given an `n x n` integer matrix.  
You can perform the following operation any number of times:

- Choose any two **adjacent** elements and multiply both by `-1`.

Two elements are adjacent if they share a border.

Return the **maximum possible sum** of all elements in the matrix after performing any number of operations.

---

## Key Insight

The operation flips the signs of **two adjacent cells together**.

This means:
- You can effectively **move negative signs** anywhere in the matrix.
- The **positions** of negatives do not matter.
- Only the **parity (even/odd)** of the count of negative numbers matters.

---

## Observations

1. You can make **almost all elements positive**.
2. If the number of negative elements is **even**, all elements can be made positive.
3. If the number of negative elements is **odd**, exactly **one element must remain negative**.
   - To maximize the sum, keep the element with the **smallest absolute value** negative.

---

## Strategy

Compute the following:
- `sumAbs` = sum of absolute values of all elements
- `negCount` = number of negative elements
- `minAbs` = minimum absolute value in the matrix

Decision:
- If `negCount` is even → answer = `sumAbs`
- If `negCount` is odd → answer = `sumAbs - 2 * minAbs`

---

## C++ Solution

```cpp
class Solution {
public:
    long long maxMatrixSum(vector<vector<int>>& matrix) {
        long long sumAbs = 0;
        int negCount = 0;
        int minAbs = INT_MAX;

        for (auto &row : matrix) {
            for (int val : row) {
                if (val < 0) negCount++;
                sumAbs += abs(val);
                minAbs = min(minAbs, abs(val));
            }
        }

        if (negCount % 2 == 0)
            return sumAbs;
        else
            return sumAbs - 2LL * minAbs;
    }
};
