# 🟦 717. 1-bit and 2-bit Characters — C++ Solution
## 📌 Problem

You’re given a binary array bits that always ends with 0.

Encoding rules:

    0 → a 1-bit character
    
    10 or 11 → a 2-bit character

Your task:
Return true if the last character must be a 1-bit character.

## 🧠 Key Idea

We simulate decoding from left to right:

    If we see a 1, it must be the start of a 2-bit character → jump 2 steps.
    
    If we see a 0, it’s a 1-bit character → jump 1 step.

The trick:

👉 We stop when we reach the last bit.
👉 If our pointer lands exactly on the last index, then it is a standalone 0 → valid 1-bit character.

## ⏱ Complexity

    Time: O(n)
    
    Space: O(1)

## 💻 C++ Solution
      class Solution {
      public:
          bool isOneBitCharacter(vector<int>& bits) {
              int i = 0;
              int n = bits.size();
          
        while (i < n - 1) {
            if (bits[i] == 1) {
                i += 2; // 2-bit character
            } else {
                i += 1; // 1-bit character
            }
        }
        
        return i == n - 1; // Did we land exactly on the last '0'?
    }
    };

## 🎯 Notes

Perfect greedy simulation

No extra data structure

Guaranteed last bit is 0 → logic always consistent
