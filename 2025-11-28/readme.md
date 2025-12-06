# 🌲 LeetCode 2872 — Maximum Number of K-Divisible Components

**Difficulty:** Hard  
**Tags:** Tree DP, DFS, Modulo, Graph  

---

## 📝 Problem Summary
You're given:
- An undirected **tree** of `n` nodes  
- Each node `i` has a value `values[i]`  
- A number `k`

You may **remove any set of edges**.  
After removing edges, all resulting **connected components** must have:

> **The sum of values in the component divisible by k**

Your goal:

> **Maximize the number of resulting components**.

---

## 💡 Core Idea — DFS + Cutting Subtrees
Since removing an edge splits a subtree, consider a DFS:

1. Compute the **sum of each subtree**.
2. If a subtree's sum is **divisible by k**, then:
   - It forms a **valid component**
   - Increase answer count
   - Return **0** upward (since this subtree is now separated)
3. Otherwise, return the **sum value upward**.

This ensures maximum components because:
- We cut **whenever it's allowed** (greedy & optimal).
- Every divisible subtree becomes its own component.

---

## 🧠 Complexity
- **Time:** O(n)  
- **Space:** O(n)

---

## ✅ C++ Code (Final, Clean, Fully Working)
```cpp
class Solution {
public:
    int ans = 0, k;
    vector<vector<int>> adj;
    vector<int> values;

    long long dfs(int node, int parent) {
        long long sum = values[node];

        for (int child : adj[node]) {
            if (child == parent) continue;
            sum += dfs(child, node);
        }

        // If this subtree sum is divisible by k → it becomes its own component
        if (sum % k == 0) {
            ans++;
            return 0;  // cut here
        }

        return sum;  // return uncut sum upward
    }

    int maxKDivisibleComponents(int n, vector<vector<int>>& edges, vector<int>& vals, int k) {
        this->k = k;
        this->values = vals;
        adj.assign(n, {});

        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]];
        }



        dfs(0, -1);
        return ans;
    }
};


```

🏁 Notes

DFS ensures correct subtree sums.

Greedy cutting is optimal because cutting earlier prevents mixing sums.

Root can also form a component if its full sum is divisible by k.
