# 🟦 1513. Number of Substrings With Only 1s — C++ Solution
## 📌 Problem

Given a binary string s, count how many substrings consist ONLY of 1s.
Return the count modulo 1,000,000,007.

## 🧠 Key Insight

Whenever you have a continuous streak of 1s of length L, it contributes:

    1+2+3+⋯+𝐿=𝐿(𝐿+1)/2

​


Instead of computing that formula repeatedly, we simply extend the streak as we scan the string:

- When we see '1':

  - Increase current streak count++

  - Add count to result

- When we see '0':

  - Reset streak to 0

## ⏱ Complexity

    Time: O(n)
    
    Space: O(1)

## 💻 C++ Code (Clean & Optimal)
    class Solution {
    public:
        int numSub(string s) {
            const long long MOD = 1e9 + 7;
            long long count = 0, result = 0;

        for (char c : s) {
            if (c == '1') {
                count++;                 // extend current streak of 1s
                result = (result + count) % MOD;
            } else {
                count = 0;               // break streak on '0'
            }
        }
        return result;
    }
    };

## 🎯 Notes

- Handles long streaks safely with modulo

- One pass, constant space

- Classic streak-counting trick for substring problems
