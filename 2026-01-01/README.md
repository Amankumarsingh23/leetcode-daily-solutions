# 66. Plus One

**Difficulty:** Easy  
**Topics:** Array, Math  

---

## Problem Statement

You are given a large integer represented as an integer array `digits`, where each `digits[i]` is the ith digit of the integer.  
The digits are ordered from most significant to least significant (left to right).  
The integer does not contain any leading zeros.

Increment the integer by one and return the resulting array of digits.

---

## Examples

### Example 1
**Input:**  
`digits = [1,2,3]`  

**Output:**  
`[1,2,4]`

### Example 2
**Input:**  
`digits = [4,3,2,1]`  

**Output:**  
`[4,3,2,2]`

### Example 3
**Input:**  
`digits = [9,9,9]`  

**Output:**  
`[1,0,0,0]`

---

## Approach

- Start from the last digit.
- If the digit is not `9`, simply increment it and return.
- If the digit is `9`, set it to `0` and propagate the carry to the left.
- If all digits are `9`, create a new array with size `n + 1` where the first digit is `1`.

---

## C++ Solution

```cpp
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int n = digits.size();

        // If last digit is not 9, just increment
        if (digits[n - 1] != 9) {
            digits[n - 1]++;
            return digits;
        }

        // Handle carry propagation
        for (int i = n - 1; i >= 0; i--) {
            if (digits[i] == 9) {
                digits[i] = 0;
            } else {
                digits[i]++;
                return digits;
            }
        }

        // All digits were 9
        vector<int> result(n + 1, 0);
        result[0] = 1;
        return result;
    }
};
