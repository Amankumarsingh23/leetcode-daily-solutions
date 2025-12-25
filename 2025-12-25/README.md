# 3074. Apple Redistribution into Boxes 🍎📦

This is a greedy problem.

## 🧠 Key Insight

You only care about the total number of apples

To minimize the number of boxes:

Pick the largest capacity boxes first

Apples can be split across boxes, so no packing constraints

# ✅ Algorithm

Compute totalApples = sum(apple)

Sort capacity in descending order

Keep adding box capacities until cumulative capacity ≥ totalApples

Count how many boxes were used

## 🚀 C++ Solution
```
class Solution {
public:
    int minimumBoxes(vector<int>& apple, vector<int>& capacity) {
        long long totalApples = 0;
        for (int a : apple) totalApples += a;

        sort(capacity.begin(), capacity.end(), greater<int>());

        long long cur = 0;
        int boxes = 0;

        for (int c : capacity) {
            cur += c;
            boxes++;
            if (cur >= totalApples) return boxes;
        }

        return boxes; // guaranteed solution exists
    }
};
```

## ⏱ Complexity
| Metric | Value                    |
| ------ | ------------------------ |
| Time   | **O(n + m log m)**       |
| Space  | **O(1)** (in-place sort) |
)

## 🧪 Example Walkthrough

Example 1
apple = [1,3,2] → total = 6
capacity = [4,3,1,5,2] → sorted → [5,4,3,2,1]

Pick 5 → sum = 5
Pick 4 → sum = 9 ≥ 6 → answer = 2

Example 2

apple = [5,5,5] → total = 15
capacity = [7,4,2,2] → sum all = 15 → need all 4

## ❌ Common Mistakes

- ❌ Trying DP or knapsack (overkill)
- ❌ Assigning packs to single boxes (not required)
- ❌ Sorting apples instead of capacities
