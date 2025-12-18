# 🟦 3652. Best Time to Buy and Sell Stock using Strategy

✔️ LeetCode — Medium

✔️ Prefix Sum + Sliding Window Optimization

✔️ C++ Clean & Efficient Solution

## 📌 Problem Summary

You are given:

   prices[i]  →  stock price on day i

   strategy[i]  →  trading action on day i

- -1 → buy

- 0 → hold

- 1 → sell

An even integer k

🔧 One Allowed Modification

You may apply at most one modification:

Choose exactly k consecutive days

Set:

First k/2 days → 0 (hold)

Last k/2 days → 1 (sell)

## 💰 Profit Definition
profit = Σ(strategy[i] × prices[i])


There are no constraints on capital or inventory.

## 🎯 Goal

Return the maximum possible profit after applying at most one valid modification.

## 🧠 Key Insight

Initial profit can be computed directly.

The modification:

- Removes original contribution of a window

- Adds profit from forced sells in the second half

- Use prefix sums to compute window impact in O(1) time.

- Slide the window across the array and track the maximum profit.

## 🧮 Algorithm Breakdown

- s[i] → prefix sum of original profit

- t[i] → prefix sum of prices

- For every window of size k:

- Remove old contribution

- Add forced sell contribution

- Take the maximum result.

## 💻 C++ Implementation (Clean & Optimized)

    class Solution {
    public:
        long long maxProfit(vector<int>& prices, vector<int>& strategy, int k) {
            int n = prices.size();
            vector<long long> s(n + 1), t(n + 1);
    
            // Prefix sums
            for (int i = 1; i <= n; i++) {
                s[i] = s[i - 1] + 1LL * prices[i - 1] * strategy[i - 1];
                t[i] = t[i - 1] + prices[i - 1];
            }
    
            long long ans = s[n];
    
            // Try applying modification on every window of size k
            for (int i = k; i <= n; i++) {
                ans = max(
                    ans,
                    s[n] - (s[i] - s[i - k]) + (t[i] - t[i - k / 2])
                );
            }
    
            return ans;
        }
    };

## ⏱️ Complexity Analysis

- Time Complexity: O(n)

- Space Complexity: O(n)

- Efficient due to prefix sums and sliding window.
