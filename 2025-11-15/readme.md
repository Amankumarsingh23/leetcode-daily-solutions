# 🟦 3234. Count the Number of Substrings With Dominant Ones — C++ Solution
## 📌 Problem

You are given a binary string s.

A substring is considered to have dominant ones if:

    ones ≥ zero²

Return the total number of substrings satisfying this condition.

## 🧠 Key Ideas

🔹 Brute force is impossible

There are up to 10⁵ characters → O(n²) substrings → too slow.

🔹 Observations

- Let zero = count of zeros in the substring.

- For this zero, we need:

   - ones ≥ zero²

- zero is small because zero + zero² ≤ n.

  - For n = 10⁵ → zero ≤ ~316.

🔹 Strategy

For every possible zero:

 1. Slide a window (l…r)

 2. Maintain count of 0 and 1

 3. Shrink window from the left to satisfy:

     - zeros = zero

     - ones ≥ zero²   

 4. Count how many substrings ending at r are valid.

This gives an O( √n · n ) solution.

## 🏎 Complexity

    Time: O(n · sqrt(n))
    
    Space: O(1)

## 💻 C++ Code (Clean, Optimized, LeetCode-Accepted)
    class Solution {
    public:
        int numberOfSubstrings(string s) {
            int ans = 0;

        // Iterate through all possible number of zeros.
        for (int zero = 0; zero + zero * zero <= s.length(); ++zero) {
            int lastInvalidPos = -1;
            vector<int> count(2);
            int n = s.length();

            for (int l = 0, r = 0; r < n; ++r) {
                ++count[s[r] - '0'];

                // Shrink from the left while maintaining minimum valid structure.
                for (; l < r; ++l) {
                    if (s[l] == '0' && count[0] > zero) {
                        --count[0];       // remove extra 0
                        lastInvalidPos = l;
                    } 
                    else if (s[l] == '1' && count[1] - 1 >= zero * zero) {
                        --count[1];       // remove extra 1
                    } 
                    else {
                        break;            // cannot shrink further
                    }
                }

                // If valid window found
                if (count[0] == zero && count[1] >= zero * zero) {
                    // Count all valid substrings ending at r
                    ans += l - lastInvalidPos;
                }
            }
        }

        return ans;
    }
    };

## ✅ Why This Works

- We fix how many zeros the substring should contain.

- Then we only need to enforce the square condition for ones.

- Efficient contraction ensures minimal window length.

- Every valid window contributes multiple substrings ending at r.
