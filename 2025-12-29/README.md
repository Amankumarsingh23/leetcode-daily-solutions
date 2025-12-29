# 756. Pyramid Transition Matrix

This is a classic DFS + backtracking with pruning problem.

## 🧠 Core Idea

- Each pair of adjacent blocks in the current row determines possible blocks above it using allowed.

- Build the pyramid row by row, from bottom → top.

- Try all valid combinations for the next row.

- Use memoization to avoid recomputing failed states (important to avoid TLE).

## 🚀 Algorithm

Convert allowed into a map:

"AB" → {C, D, ...}


DFS function:

Input: current row string

If length == 1 → success

Generate all possible next rows

Recurse on each

Memoize failed rows to prune recursion

## ✅ C++ Solution (Optimized & Accepted)
```

class Solution {
public:
    unordered_map<string, vector<char>> mp;
    unordered_set<string> bad;

    bool dfs(string curr) {
        if (curr.size() == 1) return true;
        if (bad.count(curr)) return false;

        vector<string> nextRows;
        buildNext(curr, 0, "", nextRows);

        for (auto &next : nextRows) {
            if (dfs(next)) return true;
        }

        bad.insert(curr);
        return false;
    }

    void buildNext(string &curr, int idx, string temp, vector<string> &res) {
        if (idx == curr.size() - 1) {
            res.push_back(temp);
            return;
        }

        string key = curr.substr(idx, 2);
        if (!mp.count(key)) return;

        for (char c : mp[key]) {
            buildNext(curr, idx + 1, temp + c, res);
        }
    }

    bool pyramidTransition(string bottom, vector<string>& allowed) {
        for (auto &s : allowed) {
            mp[s.substr(0, 2)].push_back(s[2]);
        }
        return dfs(bottom);
    }
};
```

## ⏱ Complexity
| Aspect | Value                            |
| ------ | -------------------------------- |
| Time   | Exponential (but heavily pruned) |
| Space  | O(states × row length)           |


Memoization ensures this passes comfortably within limits.

## 🔍 Example

bottom = "BCD"
allowed = ["BCG","CDE","GEA","FFF"]

"BC" → G

"CD" → E

Next row = "GE"

"GE" → A

Top reached ✔
