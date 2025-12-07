# 🔢 LeetCode 1018 — Binary Prefix Divisible By 5

## 📝 Problem Summary
You are given a binary array `nums`, where each element is either `0` or `1`.

Define `x_i` as the decimal number formed by the binary prefix `nums[0..i]`.

Example:  
If `nums = [1,0,1]`  
- `x0 = 1`  
- `x1 = 2`  
- `x2 = 5`

Return a boolean array `answer` where:
```
answer[i] = true  if x_i is divisible by 5
answer[i] = false otherwise
```

---

## 💡 Key Insight
The binary number formed by prefixing bits can grow extremely large.  
But to check divisibility by 5, we **only need the current prefix modulo 5**.

Updating rule for each bit:
```
current = (current * 2 + bit) % 5
```

If `current == 0`, then the prefix number is divisible by 5.

---

## 🧠 Approach
1. Start with `current = 0` (stores prefix mod 5).
2. For each bit in `nums`:
   - Update prefix modulo using binary shift.
   - Check if divisible by 5 (i.e., `current == 0`).
3. Push boolean result into `ans`.

---

## ⏱️ Time & Space Complexity
- **Time Complexity:** `O(n)`  
- **Space Complexity:** `O(n)` (output array)

---

## ✅ C++ Solution
```cpp
class Solution {
public:
    vector<bool> prefixesDivBy5(vector<int>& nums) {
        vector<bool> ans;
        int current = 0;

        for (int bit : nums) {
            current = (current * 2 + bit) % 5;
            ans.push_back(current == 0);
        }

        return ans;
    }
};
```

---

## 🔍 Example
### Input:
```
nums = [0,1,1]
```

### Output:
```
[true, false, false]
```

Explanation:  
Binary prefixes → `0`, `01`, `011`  
Decimal → `0`, `1`, `3`  
Only `0` is divisible by 5.

---

