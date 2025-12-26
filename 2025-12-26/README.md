## 2483. Minimum Penalty for a Shop

**Difficulty:** Medium  
**Topics:** Prefix Sum  
**Companies:** LeetCode  

---

### Problem Statement

You are given a string `customers` consisting only of characters `'Y'` and `'N'`.

- `'Y'` means customers come at that hour.
- `'N'` means no customers come at that hour.

If the shop closes at hour `j` (`0 <= j <= n`):

- For every hour the shop is **open** and no customers come → penalty +1
- For every hour the shop is **closed** and customers come → penalty +1

Return the **earliest hour** at which the shop must be closed to incur the **minimum penalty**.

---

### Approach

We use **prefix sums** and **suffix sums**:

- `pre[i]` → number of `'N'` in hours `[0, i-1]` (penalty while open)
- `post[i]` → number of `'Y'` in hours `[i, n-1]` (penalty while closed)

For each possible closing hour `i`, total penalty is:

    penalty = pre[i] + post[i]


We compute this for all `i` and return the **earliest index** with the minimum penalty.

---

### Time & Space Complexity

- **Time:** O(n)
- **Space:** O(n)

---

### C++ Solution

```cpp
class Solution {
public:
    int bestClosingTime(string customers) {
        int n = customers.length();
        vector<int> pre(n + 1, 0), post(n + 1, 0);

        // Prefix count of 'N'
        for (int i = 0; i < n; i++) {
            pre[i + 1] = pre[i] + (customers[i] == 'N');
        }

        // Suffix count of 'Y'
        for (int i = n - 1; i >= 0; i--) {
            post[i] = post[i + 1] + (customers[i] == 'Y');
        }

        int minPenalty = INT_MAX;
        int bestHour = 0;

        for (int i = 0; i <= n; i++) {
            int penalty = pre[i] + post[i];
            if (penalty < minPenalty) {
                minPenalty = penalty;
                bestHour = i;
            }
        }

        return bestHour;
    }
};

```
## Key Insight

- The penalty calculation splits naturally into:

- mistakes made before closing

- mistakes made after closing

- Prefix + suffix sums make this optimal and clean.


