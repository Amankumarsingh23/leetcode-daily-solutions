# 🟦 2654. Minimum Number of Operations to Make All Array Elements Equal to 1  
**LeetCode — Medium | GCD | Subarray | Math**

---

## 📌 Problem Summary

You are given a 0-indexed array `nums` of **positive integers**.

You may perform this operation any number of times:

> Choose an index `i` (0 ≤ i < n−1)  
> Replace **either** `nums[i]` **or** `nums[i+1]` with `gcd(nums[i], nums[i+1])`.

Your task:

### ✔️ Make **all elements equal to 1**  
### ✔️ Return the **minimum number of operations**  
### ✖️ If impossible → return **-1**

---

## 🧠 Key Insight & Logic

### 🔹 Step 1 — Check if it’s even possible  
If the **GCD of the entire array > 1**, then nothing can ever become 1.  
So directly return:

  if overall_gcd != 1 → return -1


---

### 🔹 Step 2 — Case when 1 already exists  
If the array already contains `'1'`:

- It takes **1 operation** to convert any neighbor to 1.
- To convert all n elements → need `(n - count_of_ones)` operations.

This gives:

 answer = n - ones_count

 
---

### 🔹 Step 3 — No 1 exists  
We must **create the first 1** by repeatedly applying GCD on a subarray whose gcd becomes 1.

We find:

> The *smallest subarray* `[i, j]` where  
> `gcd(nums[i] ... nums[j]) == 1`

If its length = `L`, then:

- We need **L−1 operations** to reduce that segment to a single `1`
- Then **(n−1) operations** to spread the `1` everywhere else.

Total:
    operations = (L - 1) + (n - 1)



---

## 💻 C++ Code (Clean & Fully Working)

```cpp
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        
        // Step 1: Check if possible (overall GCD must be 1)
        int overall_gcd = nums[0];
        for (int i = 1; i < n; i++) {
            overall_gcd = gcd(overall_gcd, nums[i]);
        }
        if (overall_gcd != 1) {
            return -1;
        }
        
        // Step 2: Count ones
        int ones_count = 0;
        for (int num : nums) {
            if (num == 1) {
                ones_count++;
            }
        }
        if (ones_count > 0) {
            return n - ones_count;
        }
        
        // Step 3: Find smallest subarray with GCD = 1
        int min_len = INT_MAX;
        for (int i = 0; i < n; i++) {
            int current_gcd = nums[i];
            for (int j = i; j < n; j++) {
                current_gcd = gcd(current_gcd, nums[j]);
                if (current_gcd == 1) {
                    min_len = min(min_len, j - i + 1);
                    break;
                }
            }
        }
        
        // Operations = (min_len - 1) to create first 1 + (n - 1) to convert the rest
        return min_len - 1 + n - 1;
    }
    
private:
    int gcd(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }
};

```

## ✅ Complexity

    Task	Complexity
    Checking global gcd	O(n)
    Finding smallest gcd=1 subarray	O(n²) (worst case)
    Space	O(1)
    
    Efficient enough because n ≤ 2000.
    
    




