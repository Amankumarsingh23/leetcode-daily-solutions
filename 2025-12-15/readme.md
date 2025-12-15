# 2110. Number of Smooth Descent Periods of a Stock

## Problem Statement

You are given an integer array `prices` where `prices[i]` is the stock price on the `i`th day.

A **smooth descent period** is a contiguous subarray such that:

- The first day can have any value
- For every following day `i`:
  prices[i] = prices[i - 1] - 1
- A single day is always a valid smooth descent period

Return the total number of smooth descent periods.

---

## Example

Input:
```
prices = [3, 2, 1, 4]
```

Output:
```
7
```

Explanation:
Valid smooth descent periods are:
```
[3], [2], [1], [4],
[3,2], [2,1],
[3,2,1]
```

---

## Approach

We traverse the array once and maintain a variable `streak`:

- `streak` = length of the current smooth descent ending at index `i`
- If `prices[i] == prices[i-1] - 1`, extend the streak
- Otherwise, reset the streak to `1`
- Add the current `streak` to the answer

Each day contributes exactly `streak` smooth descent periods.

---

## Algorithm

1. Initialize:
   - `ans = 1`
   - `streak = 1`
2. Loop from index `1` to `n - 1`
3. If current price is exactly one less than previous:
   - Increment `streak`
4. Else:
   - Reset `streak = 1`
5. Add `streak` to `ans`
6. Return `ans`

---

## C++ Solution

```cpp
class Solution {
public:
    long long getDescentPeriods(vector<int>& prices) {
        long long ans = 1;
        long long streak = 1;

        for (int i = 1; i < prices.size(); i++) {
            if (prices[i] == prices[i - 1] - 1) {
                streak++;
            } else {
                streak = 1;
            }
            ans += streak;
        }

        return ans;
    }
};
```

---

## Complexity Analysis

Time Complexity:
```
O(n)
```

Space Complexity:
```
O(1)
```

---

## Key Insight

At every index, the number of smooth descent periods ending there is equal to the length of the current descent streak.

---

