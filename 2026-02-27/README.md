# Minimum Operations to Flip Binary String to All Ones 🎯

## 🧩 Problem Summary
You are given a binary string `s` and an integer `k`. In one operation, you must choose **exactly** `k` bits and flip them (`0` becomes `1`, and `1` becomes `0`). 

**Goal:** Find the minimum number of operations to make all characters in the string `1`. If it's impossible, return `-1`.

---

## 🧠 Key Idea: State Space Reduction
The "naive" way to solve this is to treat every unique string as a state in a BFS. However, for a string of length $n$, there are $2^n$ states—too many!

**Crucial Observation:** The specific positions of the `0`s don't matter; only the **total count of `0`s** matters.
* **State:** `cur` = current number of `0`s in the string.
* **Target:** `0` zeros (all characters are `1`).

### Mathematical Transition
Suppose you have `cur` zeros and you choose to flip $x$ of them. This means you must also flip $(k - x)$ ones to satisfy the "flip exactly $k$ bits" rule.
* The $x$ zeros become ones: $-x$
* The $(k - x)$ ones become zeros: $+(k - x)$
* **New count of zeros:** $next\_cur = cur - x + (k - x) = \mathbf{cur + k - 2x}$

### Finding the Range of $x$
To find all possible next states, we need the valid range of $x$ (number of zeros we can flip):
1.  We can't flip more zeros than we have: $x \le cur$
2.  We can't flip more zeros than the total allowed: $x \le k$
3.  We can't flip more ones than we have: $(k - x) \le (n - cur) \implies x \ge k - n + cur$
4.  Standard bound: $x \ge 0$

**Valid Range:** $x \in [\max(0, k - n + cur), \min(cur, k)]$

---

## 🚀 Optimized BFS with Parity Sets
Because $next\_cur = cur + k - 2x$, notice that the parity (even/odd) of the number of zeros changes by the parity of $k$ every step. To avoid $O(N^2)$ checks, we use two `std::set`s (one for even counts, one for odd counts) to store **unvisited** states and use `lower_bound` to quickly find states within our calculated range.



---

## 💻 C++ Solution

```cpp
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <algorithm>

class Solution {
public:
    int minOperations(std::string s, int k) {
        int n = s.length();
        // Store unvisited counts in two sets based on parity (even vs odd)
        std::set<int> unvisited[2];
        for (int i = 0; i <= n; ++i) {
            unvisited[i % 2].insert(i);
        }

        int cnt0 = 0;
        for (char c : s) if (c == '0') cnt0++;

        // Initial state
        unvisited[cnt0 % 2].erase(cnt0);
        std::queue<int> q;
        q.push(cnt0);

        int operations = 0;
        while (!q.empty()) {
            int level_size = q.size();
            while (level_size--) {
                int cur = q.front();
                q.pop();

                if (cur == 0) return operations;

                // Calculate valid range of x (zeros to flip)
                int min_x = std::max(0, k - (n - cur));
                int max_x = std::min(cur, k);

                // Resulting number of zeros: cur + k - 2*x
                // next_min comes from max_x, next_max comes from min_x
                int next_min = cur + k - 2 * max_x;
                int next_max = cur + k - 2 * min_x;

                auto& targets = unvisited[next_min % 2];
                auto it = targets.lower_bound(next_min);
                
                // Efficiently visit and erase all reachable unvisited states
                while (it != targets.end() && *it <= next_max) {
                    q.push(*it);
                    it = targets.erase(it);
                }
            }
            operations++;
        }

        return -1;
    }
};
