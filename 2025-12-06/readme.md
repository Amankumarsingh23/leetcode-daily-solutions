# 🧩 LeetCode 3578 — Count Partitions With Max–Min Difference ≤ K

**Difficulty:** Medium  
**Tags:** DP, Sliding Window, Prefix Sum, Monotonic Queue

---

## 📝 Summary
Partition the array into one or more contiguous segments such that for every segment:

> `max(segment) – min(segment) ≤ k`

Return the total number of valid partitions modulo **1e9 + 7**.

---

## 💡 Intuition
We expand a sliding window from left to right.  
For each position `right`, we want to know how many valid `left` indices can start a segment ending at `right`.  
We keep track of max and min in the window using **monotonic deques** and compute DP using prefix sums.

---

## 🧠 Approaches

### 1. Brute Force (Inefficient)
- Try all possible `left` and `right` pairs and compute max/min inside the segment.
- Very slow for large inputs.

**Complexity:**  
- **Time:** O(n³) or O(n²) with better max/min tracking  
- **Space:** O(1)

(No code included because brute force is not practical.)

---

### 2. Optimized DP + Sliding Window + Prefix Sums
#### ✔ Maintain max & min in window using two deques  
#### ✔ Shrink window until valid  
#### ✔ All starts in `[left .. right]` are valid  
#### ✔ Use prefix sums to compute DP efficiently  

**Complexity:**  
- **Time:** O(n)  
- **Space:** O(n)

#### ✅ C++ Code
```cpp
class Solution {
public:
    static const int MOD = 1e9 + 7;

    int countPartitions(vector<int>& nums, int k) {
        int n = nums.size();
        vector<long long> dp(n + 1, 0), pref(n + 1, 0);

        dp[0] = 1;
        pref[0] = 1;

        deque<int> maxQ, minQ;
        int left = 0;

        for (int right = 0; right < n; right++) {

            // Maintain max deque
            while (!maxQ.empty() && nums[maxQ.back()] <= nums[right])
                maxQ.pop_back();
            maxQ.push_back(right);

            // Maintain min deque
            while (!minQ.empty() && nums[minQ.back()] >= nums[right])
                minQ.pop_back();
            minQ.push_back(right);

            // Shrink window until valid
            while (!maxQ.empty() && !minQ.empty() &&
                   nums[maxQ.front()] - nums[minQ.front()] > k) {

                if (maxQ.front() == left) maxQ.pop_front();
                if (minQ.front() == left) minQ.pop_front();
                left++;
            }

            // dp[right+1] = sum of dp[left .. right]
            long long total = pref[right] - (left > 0 ? pref[left - 1] : 0);
            total = (total % MOD + MOD) % MOD;

            dp[right + 1] = total;
            pref[right + 1] = (pref[right] + dp[right + 1]) % MOD;
        }

        return dp[n];
    }
};
