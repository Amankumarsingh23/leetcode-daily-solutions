# 1404. Number of Steps to Reduce a Number in Binary Representation to One ⚡

## 🧩 Problem Summary
Given a binary string `s`, you need to calculate the number of steps to reduce it to `"1"` by following these rules:
1.  **If the current number is even:** Divide it by 2.
2.  **If the current number is odd:** Add 1 to it.

**Constraint Alert:** The string `s` can be up to 500 characters long. Converting this to a standard integer will cause an **overflow**. We must handle the logic directly on the binary string.

---

## 🧠 Key Insight: The "Carry" Strategy
Instead of literally adding 1 to the string and re-scanning (which would be $O(N^2)$), we can traverse the string **from right to left** once ($O(N)$) and use a `carry` variable.

* **Dividing by 2** in binary is just shifting right (removing the last bit). This always takes **1 step**.
* **Adding 1** to an odd number makes it even, which then requires a division. This sequence (Add + Divide) takes **2 steps**.
* Any time we encounter an odd number or a bit that becomes `1` due to a carry, a new `carry` is generated and propagates to the left.



---

## 💻 Optimal C++ Solution ($O(N)$)

This approach avoids string manipulation and large number conversions by simulating the carry bit.

```cpp
class Solution {
public:
    int numSteps(string s) {
        int steps = 0;
        int carry = 0;

        // Traverse from right to left, stopping before the first bit (MSB)
        for (int i = s.size() - 1; i > 0; i--) {
            int currentBit = (s[i] - '0') + carry;

            if (currentBit == 1) {
                // The number is odd: 1 step to add 1, 1 step to divide by 2
                steps += 2;
                carry = 1; 
            } else {
                // The number is even (0+0 or 1+1 carry): 1 step to divide
                steps += 1;
                // carry remains the same (if it was 1, it stays 1; if 0, stays 0)
            }
        }

        // If a carry reaches the leftmost '1', it turns '1' into '10'
        // '10' needs one more division to become '1'.
        return steps + carry;
    }
};
