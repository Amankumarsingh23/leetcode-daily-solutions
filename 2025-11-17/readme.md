# 🟦 1437. Check If All 1’s Are at Least K Places Away — C++ Solution
## 📌 Problem

You are given:

A binary array nums

An integer k

Return true if every pair of 1’s in the array are at least k zeros apart.

## 🧠 Key Insight

Track the index of the previous 1:

    For each 1 at position i
    
    If we saw a previous 1 at prev
    
    Check if the gap (i - prev - 1) is at least k
    
    If not → return false
    
    Update prev = i each time we find a new 1.

## ⏱ Complexity

    Time: O(n)
    
    Space: O(1)

## 💻 C++ Code (Clean & Optimal)
    class Solution {
    public:
        bool kLengthApart(vector<int>& nums, int k) {
            int prev = -1;  // index of previous 1
    
            for (int i = 0; i < nums.size(); i++) {
                if (nums[i] == 1) {
                    if (prev != -1 && (i - prev - 1) < k) {
                        return false;  // gap between 1s is smaller than k
                    }
                    prev = i;  // update the last seen 1
                }
            }
            return true;
        }
    };

## 🎯 Notes

Handles all cases correctly (first 1, multiple 1s, edge cases)

No extra memory

Works in a single pass
