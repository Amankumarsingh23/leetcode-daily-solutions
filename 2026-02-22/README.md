# 868. Binary Gap

## 🧩 Problem Statement

Given a **positive integer** `n`, find and return the **longest distance between any two adjacent `1`s** in the binary representation of `n`.

* Two `1`s are considered **adjacent** if there are only `0`s between them (possibly none).
* The **distance** between two `1`s is the **absolute difference between their bit positions**.

If there are **fewer than two `1`s**, return `0`.

---

## 📌 Examples

### Example 1
**Input:** `n = 22`  
**Binary Representation:** `10110`  


**Distances between adjacent `1`s:**
* First pair: positions `(4, 2)` → distance = **2**
* Second pair: positions `(2, 1)` → distance = **1**

**Output:** `2`

---

### Example 2
**Input:** `n = 8`  
**Binary Representation:** `1000`  

> [!NOTE]
> There is only one `1`, so there are no adjacent pairs.

**Output:** `0`

---

## 🧠 Intuition

We don’t actually need to convert the number into a binary string. Instead, we can:
* Read the binary representation **bit by bit** using **bitwise operations**.
* Track the **index of every `1`** we encounter.
* Compute the distance between the current `1` and the **previous `1`**.
* Keep updating the **maximum distance**.

This approach is faster, memory-efficient, and follows a classic bit-manipulation pattern.

---

## ⚙️ Approach

1.  Start scanning bits from **right to left** (Least Significant Bit first).
2.  Maintain:
    * `lastPos`: position of the previous `1`.
    * `pos`: current bit position.
    * `maxGap`: the final answer.
3.  For each bit:
    * If the bit is `1`:
        * If we've seen a `1` before (`lastPos != -1`), compute: `gap = pos - lastPos`.
        * Update `maxGap` if the current gap is larger.
        * Update `lastPos = pos`.
4.  Shift the number right (`n >>= 1`) to process the next bit and increment `pos`.
5.  Continue until `n` becomes `0`.

---

## 💻 C++ Solution

```cpp
class Solution {
public:
    int binaryGap(int n) {
        int lastPos = -1;   // Stores position of previous '1'
        int maxGap = 0;     // Stores maximum distance found
        int pos = 0;        // Current bit position

        while (n > 0) {
            if (n & 1) {  // Check if current bit is 1
                if (lastPos != -1) {
                    maxGap = max(maxGap, pos - lastPos);
                }
                lastPos = pos;
            }

            n >>= 1;  // Shift right to check next bit
            pos++;
        }

        return maxGap;
    }
};
