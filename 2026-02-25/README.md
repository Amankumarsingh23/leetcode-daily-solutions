# 1356. Sort Integers by The Number of 1 Bits 🔢✨

## 🧩 Problem Summary
Given an integer array `arr`, sort the integers in the following order:
1.  **Primary Sort:** By the number of **1s** (set bits) in their binary representation in ascending order.
2.  **Secondary Sort:** If two or more integers have the same number of set bits, sort them by their **numerical value** in ascending order.

---

## 🔎 Example Breakdown
**Input:** `arr = [0, 1, 2, 3, 4, 5, 6, 7, 8]`

| Number | Binary | No. of 1 bits |
| :--- | :--- | :--- |
| **0** | `0000` | 0 |
| **1** | `0001` | 1 |
| **2** | `0010` | 1 |
| **4** | `0100` | 1 |
| **8** | `1000` | 1 |
| **3** | `0011` | 2 |
| **5** | `0101` | 2 |
| **6** | `0110` | 2 |
| **7** | `0111` | 3 |

**Result:** `[0, 1, 2, 4, 8, 3, 5, 6, 7]`

---

## 🧠 Key Idea: Custom Sorting
To solve this efficiently, we use the C++ STL `std::sort` with a **custom comparator**.

1.  **Counting Bits:** We use the built-in GCC function `__builtin_popcount(x)`, which is highly optimized (often a single CPU instruction) to count set bits.
2.  **Comparison Logic:**
    * If `popcount(a) != popcount(b)`, return `popcount(a) < popcount(b)`.
    * Otherwise, return `a < b`.



---

## 💻 C++ Solution (Using Lambda)

Using a lambda function inside `sort` makes the code concise and keeps the logic localized.

```cpp
class Solution {
public:
    vector<int> sortByBits(vector<int>& arr) {
        sort(arr.begin(), arr.end(), [](const int& a, const int& b) {
            int countA = __builtin_popcount(a);
            int countB = __builtin_popcount(b);

            // If bit counts are equal, sort by actual value (Secondary Sort)
            if (countA == countB) {
                return a < b;
            }
            
            // Otherwise, sort by number of set bits (Primary Sort)
            return countA < countB;
        });

        return arr;
    }
};
