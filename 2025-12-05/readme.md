# 3432. Count Partitions with Even Sum Difference
**Language:** C++  
**Solution file:** `3432_count_partitions_with_even_sum_difference.cpp`

---

## 📝 Summary
A partition splits the array into a left and right subarray.  
We need to count how many such partitions result in an **even difference** between left sum and right sum.

---

## 💡 Intuition
The difference between the two partition sums is:

```
(left_sum) - (right_sum)
= left_sum - (total_sum - left_sum)
= 2 * left_sum - total_sum
```

For this expression to be **even**, the **total_sum must be even**.  
If the total sum is odd → no way to make the difference even.

If total sum is even → **every partition is valid**.

---

## 🧠 Approaches

### **1. Direct Mathematical Approach (Optimized & Simple)**

#### ✔ Key Insight
`2 * left_sum` is always even →  
`2 * left_sum - total_sum` is even ⟺ `total_sum` is even.

So:

- If `total_sum` is **even** → all `(n - 1)` partitions work  
- If `total_sum` is **odd** → `0` partitions work

#### **Complexity**
- **Time:** O(n)  
- **Space:** O(1)

---

## 🧾 Code (C++)
```cpp
class Solution {
public:
    int countPartitions(vector<int>& nums) {
        long long total = 0;
        for (int x : nums) total += x;

        int n = nums.size();

        // If total sum is even, all (n-1) partitions are valid
        if (total % 2 == 0)
            return n - 1;

        // Otherwise, no valid partitions
        return 0;
    }
};
```

---

## 📌 Final Notes
- The entire problem reduces to parity of the total sum.  
- No prefix sums, no extra arrays, no brute force needed.  
- One of the cleanest O(n) mathematical solutions.

