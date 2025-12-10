# 🟦 3577. Count the Number of Computer Unlocking Permutations  
**LeetCode — Medium | Graph / DP Logic**

---

## 📌 Problem Summary

You are given:

- `n` computers labeled `0 … n-1`
- An array `complexity[i]` representing the password complexity of each computer
- Computer **0** is already unlocked and acts as the **root**

To unlock computer `i`, you must have already unlocked some computer `j` such that:

- `j < i`  
- `complexity[j] < complexity[i]`

---

## ❗ Goal  
Find the number of permutations of `[0, 1, 2, …, n−1]` that correspond to **valid unlocking orders**.

Return result modulo:

     10^9+7


---

## 🧠 Key Insight (Why the solution is so simple)

### 🔹 Fact 1  
Computer **0** is unlocked from the start, but still appears in the permutation at index `0`.

### 🔹 Fact 2  
Each computer `i > 0` must be unlocked **after** at least one index `j < i` with:

   `complexity[j] < complexity[i]`


Then even computer 0 (the smallest j) cannot unlock it.

➡️ **Unlocking is impossible → answer = 0**

---

## 🔹 If all complexity[i] > complexity[0]

Then:

- Computer 0 can unlock every computer.
- Every permutation of `1, 2, 3, ..., (n−1)` is valid.

So total valid orders = 

    (n - 1)!

---

## 🧮 Final Formula

- If **any** `complexity[i] <= complexity[0]` (for i ≥ 1):  
  → return **0**

- Else:  
  → return **(n - 1)! mod 1e9+7**

---

## 💻 C++ Code (Clean & Optimal)

```cpp
class Solution {
public:
    int countPermutations(vector<int>& complexity) {
        const int mod = 1e9 + 7;
        long long ans = 1;

        for (int i = 1; i < complexity.size(); ++i) {
            if (complexity[i] <= complexity[0]) {
                return 0;        // impossible to unlock computer i
            }
            ans = ans * i % mod; // building factorial (n-1)!
        }

        return ans;
    }
};

```
## ✅ Complexity Analysis

    Time Complexity: O(n)
    Space Complexity: O(1)
    Just linear scanning + factorial computation.
