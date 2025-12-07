# 📈 LeetCode 3381 — Maximum Subarray Sum With Length Divisible by K

Difficulty: Medium
Tags: Prefix Sum, Modulo, DP, Subarray

## 📝 Problem Summary

You're given:
        
        An integer array nums
        
        An integer k

Your task:

        Find the maximum subarray sum such that the subarray length is divisible by k.

A subarray is valid if:

        (r - l + 1) % k == 0

## 💡 Core Idea — Prefix Sum + Modulo Classes

Key observation:

For a subarray l..r:
        
        length = r - l + 1
        (r + 1) % k == l % k


This means:

✔ Two prefix sums must have the same modulo
✔ To maximize subarray sum, subtract the smallest prefix with that modulo

So we maintain:

prefix = running sum

best[r] = minimum prefix sum seen for modulo class r

At index i:

        r = (i + 1) % k
        candidate = prefix - best[r]


Update answer and update best[r].

## 🕒 Complexity

Time: O(n)

Space: O(k)

## ✅ C++ Code (Final, Clean, Fully Working)
''''

        
        class Solution {
               public:
                   long long maxSubarraySum(vector<int>& nums, int k) {
                       int n = nums.size();
                       vector<long long> best(k, LLONG_MAX);
                     long long prefix = 0, ans = LLONG_MIN;
                       best[0] = 0;  // prefix before starting

                             for(int i = 0; i < n; i++){
                                 prefix += nums[i];
                                 int r = (i + 1) % k;
                     
                                 if(best[r] != LLONG_MAX)
                                     ans = max(ans, prefix - best[r]);
                     
                                 best[r] = min(best[r], prefix);
                             }
                     
                             return ans;
                         }
                           };
''''
## 📌 Notes

Classic prefix sum + modulo equivalence trick

best[r] ensures subarray length is divisible by k

Using LLONG_MIN/MAX handles negative numbers safely
