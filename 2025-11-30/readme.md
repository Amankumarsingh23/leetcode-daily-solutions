# 🔢 LeetCode 1590 — Make Sum Divisible by P

**Difficulty:** Medium  
**Tags:** Prefix Sum, Hash Map, Modular Arithmetic, Sliding Window  

---

## 📝 Problem Summary
You are given an array of **positive integers** `nums` and an integer `p`.  
Your task:

> Remove the *smallest subarray* such that the sum of the remaining elements is divisible by **p**.

Constraints:
- You **cannot** remove the entire array.
- If impossible, return **-1**.

---

## 💡 Intuition
Let:
- `S = total sum of nums`
- `r = S % p`  

To make the remaining sum divisible by `p`, we must remove a subarray whose sum ≡ `r` (mod `p`).

So we just need to find:

> **Smallest subarray whose prefix difference ≡ r mod p**

Use:
- prefix sums mod p  
- hashmap storing earliest index for each mod value  
- sliding window over prefix values

---

## 🧠 Approaches

### 1. Brute Force (Too slow)
Try every subarray and check if sum removed has mod `r`.

**Complexity:**  
- **Time:** O(n²)  
- **Space:** O(1)

(Not included due to inefficiency.)

---

### 2. Optimized Prefix + HashMap (Best Approach)

Track prefix sums mod `p` and search for:
(prefix - remainder + p) % p

This gives the needed subarray sum modulo.

**Complexity:**  
- **Time:** O(n)  
- **Space:** O(n)

---

## ✅ C++ Code (Optimized)
```cpp
class Solution {
 public:
  int minSubarray(vector<int>& nums, int p) {
    const long sum = accumulate(nums.begin(), nums.end(), 0L);
    const int remainder = sum % p;
    if (remainder == 0)
      return 0;

    unordered_map<int, int> prefixToIndex{{0, -1}};
    int ans = nums.size();
    int prefix = 0;

    for (int i = 0; i < nums.size(); ++i) {
      prefix += nums[i];
      prefix %= p;
      const int target = (prefix - remainder + p) % p;

      if (const auto it = prefixToIndex.find(target);
          it != prefixToIndex.cend())
        ans = min(ans, i - it->second);

      prefixToIndex[prefix] = i;
    }

    return ans == nums.size() ? -1 : ans;
  }
};


````
🏁 Final Notes

Removes subarray with smallest length.

Fully O(n) using modular prefix sums.

Handles edge cases like already divisible or impossible scenarios.
