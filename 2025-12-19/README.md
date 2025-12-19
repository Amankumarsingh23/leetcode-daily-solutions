# 2092 Find All People With Secret ✅

(no TLE, no wrong edge cases)

## 🧠 Key Insight


- Meetings at the same time happen simultaneously

- A person who learns the secret at time t can immediately share it with others at the same t

- But connections do NOT persist across different times unless the person already has the secret

So we must:

1. Group meetings by time

2. For each time group:

    - Build temporary connections

    - Spread the secret only inside that group

    - Reset connections after processing that time

## 🚀 Correct Approach (Union-Find per time block)
Steps

1. Sort meetings by time

2. Track who currently knows the secret

3. For each time:

    - Union people meeting at that time

    - If anyone in a connected component knows the secret, everyone in that component gets it

    - Reset DSU for next time

## ✅ C++ Solution
```
class Solution {
public:
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        vector<int> parent(n), rank(n, 0);
        vector<bool> hasSecret(n, false);

        iota(parent.begin(), parent.end(), 0);

        function<int(int)> find = [&](int x) {
            if (parent[x] != x)
                parent[x] = find(parent[x]);
            return parent[x];
        };

        auto unite = [&](int a, int b) {
            a = find(a);
            b = find(b);
            if (a == b) return;
            if (rank[a] < rank[b]) swap(a, b);
            parent[b] = a;
            if (rank[a] == rank[b]) rank[a]++;
        };

        hasSecret[0] = hasSecret[firstPerson] = true;

        sort(meetings.begin(), meetings.end(),
             [](auto &a, auto &b) { return a[2] < b[2]; });

        int i = 0;
        while (i < meetings.size()) {
            int t = meetings[i][2];
            vector<int> people;

            // process all meetings at time t
            while (i < meetings.size() && meetings[i][2] == t) {
                unite(meetings[i][0], meetings[i][1]);
                people.push_back(meetings[i][0]);
                people.push_back(meetings[i][1]);
                i++;
            }

            // mark components that know the secret
            unordered_set<int> secretRoots;
            for (int p : people) {
                if (hasSecret[p])
                    secretRoots.insert(find(p));
            }

            // spread secret
            for (int p : people) {
                if (secretRoots.count(find(p)))
                    hasSecret[p] = true;
            }

            // reset DSU for next time
            for (int p : people) {
                parent[p] = p;
                rank[p] = 0;
            }
        }

        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (hasSecret[i]) ans.push_back(i);
        }
        return ans;
    }
};
```


## ⏱ Complexity

| Metric | Value          |
| ------ | -------------- |
| Time   | **O(m log m)** |
| Space  | **O(n)**       |

(m = meetings.size())

## 🧪 Why This Works

✔ Handles instant sharing at same timestamp
✔ Prevents invalid propagation across times
✔ Uses temporary DSU correctly
✔ Matches all LeetCode edge cases

## 🏆 Pattern Recognized

This is a classic:

        "Temporal Graph + DSU Reset" problem

Similar problems:

    - Information spread

    - Virus transmission

    - Event-based connectivity