# 🔢 LeetCode 262 — Greatest Sum Divisible by Three

## 📝 Problem Summary
You are given an integer array `nums`.  
Your task: **Return the maximum possible sum of elements such that the total sum is divisible by 3.**

---

## 💡 Key Insight
- Every number has a remainder of **0, 1, or 2** when divided by 3.
- Let `sum = total sum of all elements`.

### Cases:
- If `sum % 3 == 0` → already valid.
- If `sum % 3 == 1` → remove the **smallest possible amount** to make it divisible:
  - Option A: remove **one** smallest element with remainder `1`.
  - Option B: remove **two** smallest elements with remainder `2`.

- If `sum % 3 == 2` → symmetric:
  - Option A: remove **one** smallest element with remainder `2`.
  - Option B: remove **two** smallest elements with remainder `1`.

Choose the option that reduces the sum **the least**.

---

## 🧠 Approach
1. Compute total sum.
2. Separate numbers into two lists:
   - `rem1`: numbers with `num % 3 == 1`
   - `rem2`: numbers with `num % 3 == 2`
3. If sum is divisible by 3 → return it.
4. Otherwise remove the smallest set of elements based on the remainder.
5. Return the adjusted maximum sum.

---

## ⏱️ Time & Space Complexity
- **Time Complexity:** `O(n log n)` (sorting remainder groups)
- **Space Complexity:** `O(n)` (storing remainder groups)

---

## ✅ C++ Solution
```cpp
class Solution {
public:
    int maxSumDivThree(vector<int>& nums) {
        int sum = 0;
        vector<int> rem1, rem2; // store nums % 3 == 1 and nums % 3 == 2

        for (int x : nums) {
            sum += x;
            if (x % 3 == 1) rem1.push_back(x);
            else if (x % 3 == 2) rem2.push_back(x);
        }

        if (sum % 3 == 0) return sum;

        sort(rem1.begin(), rem1.end());
        sort(rem2.begin(), rem2.end());

        int ans = 0;

        if (sum % 3 == 1) {
            int option1 = rem1.size() ? rem1[0] : INT_MAX;  
            int option2 = rem2.size() > 1 ? rem2[0] + rem2[1] : INT_MAX;
            ans = sum - min(option1, option2);
        } else { // sum % 3 == 2
            int option1 = rem2.size() ? rem2[0] : INT_MAX;
            int option2 = rem1.size() > 1 ? rem1[0] + rem1[1] : INT_MAX;
            ans = sum - min(option1, option2);
        }

        return ans < 0 ? 0 : ans;
    }
};
```

---

## 🔍 Example
### Input:
```
[3,6,5,1,8]
```

### Output:
```
18
```

### Explanation:
Pick: `3 + 6 + 1 + 8 = 18`, which is the maximum sum divisible by 3.

---

