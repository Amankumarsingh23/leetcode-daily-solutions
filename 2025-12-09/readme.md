# 🟩 3583. Count Special Triplets — C++ Solution
## 📌 Problem

You are given an integer array nums.
A special triplet is a triplet of indices (i, j, k) such that:

    0 ≤ i < j < k < n
    
    nums[i] == nums[j] * 2
    
    nums[k] == nums[j] * 2

Return the count of all such triplets modulo 1e9 + 7.

## ✅ Approach

To count triplets (i, j, k) where:

    nums[i] = 2 * nums[j]
    nums[k] = 2 * nums[j]


We need:

Elements before j equal to 2 * nums[j] → left count

Elements after j equal to 2 * nums[j] → right count

## 🔹 Steps

Build a right frequency map of all numbers.

    Iterate j from 0 to n-1:

Remove the current element from the right map.

Compute:

      ans += left[2 * nums[j]] * right[2 * nums[j]]

Add the current element to the left map.

Apply modulo.

## ⏱ Complexity

Time: O(n)

Space: O(n)

## 💻 C++ Solution

    class Solution {
    public:
        static const long long MOD = 1e9 + 7;

    int specialTriplets(vector<int>& nums) {
        int n = nums.size();
        unordered_map<long long, long long> right, left;

        // Count all occurrences first (right frequency)
        for (long long x : nums) {
            right[x]++;
        }

        long long ans = 0;

        for (long long j = 0; j < n; j++) {
            long long val = nums[j];

            // Remove current j from right
            right[val]--;

            long long need = val * 2;

            long long leftCount  = left[need];
            long long rightCount = right[need];

            ans = (ans + (leftCount * rightCount) % MOD) % MOD;

            // Add current j to left
            left[val]++;
        }

        return ans;
    }
    };

## 🎯 Clean Notes 

Perfect frequency-split technique

No nested loops

Optimal for large constraints

Uses modulo correctly
