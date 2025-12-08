# 🔮 LeetCode 1930 — Unique Length-3 Palindromic Subsequences

**Difficulty:** Medium  
**Tags:** Hashing, Two Pointers, String, Palindrome  

---

## 📝 Problem Summary
You are given a string `s`.  
You must count how many **unique palindromic subsequences** of **length 3** exist in `s`.

A valid palindrome of length 3 looks like:

```
x y x
```

Where:
- The **first** and **last** characters are the same (`x`)
- The **middle** character can be anything (`y`)
- It must be a **subsequence** (not necessarily contiguous)
- Only **unique** palindromes are counted

---

## 💡 Key Insight
For each character `'a'` to `'z'`:

1. Find its **first** occurrence  
2. Find its **last** occurrence  

If the distance is ≥ 2, then this character can be the *outer* character of a palindrome:

```
[first_x ... middle ... last_x]
```

All **distinct characters** that appear between these two positions form valid palindromes:

```
x ? x
```

We simply collect all unique middle characters.

---

## 🧠 Approach
1. Precompute `first[c]` and `last[c]` for each character.  
2. For each character `c`:
   - If `first[c] + 2 ≤ last[c]`, then:
     - Scan the substring `(first[c] + 1) → (last[c] - 1)`
     - Insert all characters into a set
     - Add the set size to answer  
3. Return total sum.

---

## ⏱️ Complexity
- **Time:** O(26 * n) = O(n)  
- **Space:** O(26)

---

## ✅ C++ Solution
```cpp
class Solution {
public:
    int countPalindromicSubsequence(string s) {
        int n = s.size();
        vector<int> first(26, -1), last(26, -1);

        // store first and last index of each character
        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a';
            if (first[c] == -1) first[c] = i;
            last[c] = i;
        }

        int ans = 0;

        // for each character as first and last element
        for (int c = 0; c < 26; c++) {
            if (first[c] != -1 && last[c] - first[c] >= 2) {
                unordered_set<char> inside;
                for (int i = first[c] + 1; i < last[c]; i++) {
                    inside.insert(s[i]);
                }
                ans += inside.size(); // each distinct middle char forms a palindrome
            }
        }

        return ans;
    }
};
```

---

## 🔍 Example

### Input:
```
s = "aabca"
```

### Output:
```
3
```

### Valid palindromes:
- **"aba"**
- **"aaa"**
- **"aca"**

---

