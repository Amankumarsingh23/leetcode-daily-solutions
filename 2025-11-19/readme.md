# 🟩 2154. Keep Multiplying Found Values by Two — C++ Solution
📌 Problem

You are given:

an integer array nums

an integer original

Repeat the process:
    
    If original exists in nums, update:
    original = original × 2

Else, stop.

Return the final value of original.

## ✅ Approach

Convert nums → unordered_set for O(1) lookup

While original is found → multiply by 2

Return when not found

    Time Complexity: O(n)
    Space Complexity: O(n)

## 💻 C++ Solution

      class Solution {
      public:
          int findFinalValue(vector<int>& nums, int original) {
              unordered_set<int> s(nums.begin(), nums.end());
      
              while (s.count(original)) {
                  original *= 2;
              }
      
              return original;
          }
      };

## 🎯 Notes (Same high-quality script style we follow)

Uses the simplest & fastest logic

No loops over full array

Best possible solution
