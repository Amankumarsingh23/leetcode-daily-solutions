# Discounts (Hard)

## Problem Summary

You are given:

- `n` employees (IDs `1` to `n`)
- Employee `1` is the CEO (root of the hierarchy)
- Arrays:
  - `present[i]`: price to buy employee `i`'s stock today
  - `future[i]`: price to sell employee `i`'s stock tomorrow
- A company hierarchy as a tree
- A total investment `budget`

### Discount Rule

If an employee's **direct boss buys their own stock**, then the employee can buy their stock at:

```
floor(present[i] / 2)
```

### Constraints

- Each stock can be bought at most once
- You cannot reuse future profit to buy more stocks
- Goal: **maximize total profit within the budget**

---

## Key Observations

1. The hierarchy forms a **tree** rooted at employee `1`
2. Buying a stock affects only **direct children** (discount dependency)
3. Each employee has **two states**:
   - Boss did NOT buy → full price
   - Boss DID buy → discounted price
4. Budget constraint → **knapsack DP**
5. Tree structure → **tree DP**

---

## DP State Definition

For each employee `u`, we compute:

```
dp_u[b][p]
```

Where:
- `b` = budget used
- `p` = whether parent bought stock
  - `0` → parent did NOT buy
  - `1` → parent DID buy
- Value = **maximum profit**

---

## Strategy

1. Build adjacency list from hierarchy
2. DFS from root
3. Merge children using knapsack-style DP
4. Decide whether to buy current employee's stock:
   - Cost depends on parent state
   - Profit = `future - cost`
5. Return best profit at root with full budget

---

## C++ Solution

```cpp
class Solution {
public:
    int maxProfit(int n, vector<int>& present, vector<int>& future,
                  vector<vector<int>>& hierarchy, int budget) {

        vector<vector<int>> tree(n + 1);
        for (auto &e : hierarchy) {
            tree[e[0]].push_back(e[1]);
        }

        function<vector<array<int,2>>(int)> dfs = [&](int u) {
            vector<array<int,2>> dp(budget + 1, {0, 0});

            // Merge children
            for (int v : tree[u]) {
                auto child = dfs(v);
                vector<array<int,2>> ndp(budget + 1, {0, 0});

                for (int i = 0; i <= budget; i++) {
                    for (int j = 0; j <= i; j++) {
                        for (int p = 0; p < 2; p++) {
                            ndp[i][p] = max(
                                ndp[i][p],
                                dp[i - j][p] + child[j][p]
                            );
                        }
                    }
                }
                dp = ndp;
            }

            // Decide whether to buy stock of u
            vector<array<int,2>> res(budget + 1, {0, 0});
            int sell = future[u - 1];

            for (int b = 0; b <= budget; b++) {
                for (int parentBought = 0; parentBought < 2; parentBought++) {
                    int cost = present[u - 1] / (parentBought + 1);
                    res[b][parentBought] = dp[b][0];

                    if (b >= cost) {
                        res[b][parentBought] = max(
                            res[b][parentBought],
                            dp[b - cost][1] + (sell - cost)
                        );
                    }
                }
            }

            return res;
        };

        return dfs(1)[budget][0];
    }
};
```

---

## Complexity Analysis

Let `B = budget`

- **Time Complexity:**  
  ```
  O(n * B²)
  ```

- **Space Complexity:**  
  ```
  O(n * B)
  ```

---

## Core Insight

This is a **tree knapsack DP with dependency-based discounts**.  
Each node’s decision affects only its children, making DFS + DP the perfect fit.

---

## When to Use This Pattern

- Hierarchical dependency
- Budget constraints
- Parent decision affects children
- “Buy or skip” with state transitions

---

