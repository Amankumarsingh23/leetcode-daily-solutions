# 1461. Check If a String Contains All Binary Codes of Size K 🚀

## 🧩 Problem Summary
Given a binary string `s` and an integer `k`, determine if every possible binary code of length `k` appears as a substring in `s`.

* **Total unique codes to find:** $2^k$
* **Goal:** Return `true` if all $2^k$ unique patterns exist in `s`, otherwise return `false`.

---

## 🔎 Example Walkthrough ($k = 2$)
* **Required codes:** `00`, `01`, `10`, `11` (Total = $2^2 = 4$)
* **Input string:** `"00110110"`
* **Sliding Window:**
    1.  `"00"` -> Found ✅
    2.  `"01"` -> Found ✅
    3.  `"11"` -> Found ✅
    4.  `"10"` -> Found ✅
* **Result:** `true` (All 4 patterns found).

---

## 🧠 Approach 1: Sliding Window with Hash Set
The most intuitive way is to "slice" the string into all possible segments of length $k$ and store them in a set to count unique occurrences.

### Logic
1.  Calculate `need = 1 << k` ($2^k$).
2.  Slide a window of size $k$ across the string.
3.  Insert each substring into an `unordered_set`.
4.  **Early Stop:** If the set size reaches `need`, return `true` immediately.



### 💻 C++ Implementation
```cpp
class Solution {
public:
    bool hasAllCodes(string s, int k) {
        // Optimization: If the string is too short to possibly contain all codes
        if (s.size() < (1 << k) + k - 1) return false;

        int need = 1 << k; 
        unordered_set<string> seen;

        for (int i = 0; i <= (int)s.size() - k; i++) {
            seen.insert(s.substr(i, k));
            if (seen.size() == need) return true; 
        }

        return seen.size() == need;
    }
};
