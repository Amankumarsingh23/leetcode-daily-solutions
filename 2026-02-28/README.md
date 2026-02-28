# 1680. Concatenation of Consecutive Binary Numbers 🔢⛓️

## 🧩 Problem Summary
Given an integer `n`, you need to concatenate the binary representations of all numbers from `1` to `n` in order and return the decimal value of the resulting string modulo $10^9 + 7$.

### Example Breakdown ($n = 3$)
1.  **1** in binary: `"1"`
2.  **2** in binary: `"10"`
3.  **3** in binary: `"11"`
4.  **Concatenation:** `"1" + "10" + "11" = "11011"`
5.  **Decimal Value:** $27$

---

## 🧠 Key Idea: Building the Number Mathematically
To avoid string operations (which are slow), we can build the total value $V$ iteratively. When we move from $i-1$ to $i$:
1.  **Find the length** of the binary representation of $i$. Let this be `len`.
2.  **Shift** the current total $V$ to the left by `len` positions to make room for $i$.
3.  **Add** (or OR) the value of $i$ to the shifted total.
4.  **Modulo:** Apply $10^9 + 7$ to keep the number within integer limits.

**The Formula:**
$$V_{new} = ((V_{old} \ll len) + i) \pmod{10^9 + 7}$$



### How to find the length of $i$ efficiently?
A new bit is added whenever $i$ is a power of 2 (e.g., $2, 4, 8, 16\dots$). We can keep track of this without calling `log2()` repeatedly:
* `(i & (i - 1)) == 0` is true if $i$ is a power of 2.

---

## 💻 C++ Solution

```cpp
class Solution {
public:
    int concatenatedBinary(int n) {
        long long result = 0;
        int MOD = 1e9 + 7;
        int binaryLength = 0;

        for (int i = 1; i <= n; i++) {
            // If i is a power of 2, the number of bits increases
            // Example: 2 (10), 4 (100), 8 (1000)
            if ((i & (i - 1)) == 0) {
                binaryLength++;
            }

            // Shift current result by the length of i, then add i
            result = ((result << binaryLength) + i) % MOD;
        }

        return (int)result;
    }
};
