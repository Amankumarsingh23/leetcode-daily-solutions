# 🟦 3573. Best Time to Buy and Sell Stock V
✔️ LeetCode — Medium  
✔️ Dynamic Programming  
✔️ Normal + Short Selling Transactions  
✔️ C++ Clean Solution  

---

## 📌 Problem Summary

You are given:

- An integer array `prices`, where `prices[i]` is the stock price on day `i`
- An integer `k`, the maximum number of transactions allowed

You can perform **at most `k` transactions**, and each transaction can be:

### 1️⃣ Normal Transaction
- Buy on day `i`
- Sell on day `j` where `i < j`
- Profit = `prices[j] - prices[i]`

### 2️⃣ Short Selling Transaction
- Sell on day `i`
- Buy back on day `j` where `i < j`
- Profit = `prices[i] - prices[j]`

### Constraints
- You must finish one transaction before starting another
- You cannot buy and sell on the same day
- Return the **maximum total profit**

---

## 🧠 Key Insight

This is an extension of classic stock DP, but with **three states** instead of two:

| State | Meaning |
|-----|--------|
| `0` | No active transaction |
| `1` | Holding a stock (after buy) |
| `2` | Holding a short position (after sell first) |

We track:
```
dp[day][transactions_used][state]
```

---

## 🧮 DP Transitions

### State Definitions

- `dp[i][j][0]` → Max profit on day `i`, `j` transactions, **no position**
- `dp[i][j][1]` → Holding stock (normal buy)
- `dp[i][j][2]` → Holding short position

---

### Transition Rules

```text
dp[i][j][0] =
    max(
        dp[i-1][j][0],               // do nothing
        dp[i-1][j][1] + prices[i],   // sell stock
        dp[i-1][j][2] - prices[i]    // buy back short
    )

dp[i][j][1] =
    max(
        dp[i-1][j][1],               // keep holding
        dp[i-1][j-1][0] - prices[i]  // buy stock
    )

dp[i][j][2] =
    max(
        dp[i-1][j][2],               // keep short
        dp[i-1][j-1][0] + prices[i]  // short sell
    )
```

---

## 💻 C++ Implementation

```cpp
class Solution {
public:
    long long maximumProfit(vector<int>& prices, int k) {
        int n = prices.size();
        long long dp[n][k + 1][3];
        memset(dp, 0, sizeof(dp));

        // Initialization for day 0
        for (int j = 1; j <= k; ++j) {
            dp[0][j][1] = -prices[0]; // buy
            dp[0][j][2] = prices[0];  // short sell
        }

        for (int i = 1; i < n; ++i) {
            for (int j = 1; j <= k; ++j) {
                dp[i][j][0] = max({
                    dp[i - 1][j][0],
                    dp[i - 1][j][1] + prices[i],
                    dp[i - 1][j][2] - prices[i]
                });

                dp[i][j][1] = max(
                    dp[i - 1][j][1],
                    dp[i - 1][j - 1][0] - prices[i]
                );

                dp[i][j][2] = max(
                    dp[i - 1][j][2],
                    dp[i - 1][j - 1][0] + prices[i]
                );
            }
        }

        return dp[n - 1][k][0];
    }
};
```

---

## ✅ Example

**Input**
```
prices = [1,7,9,8,2]
k = 2
```

**Output**
```
14
```

**Explanation**
- Buy at 1 → Sell at 9 → Profit = 8
- Short sell at 8 → Buy back at 2 → Profit = 6  
**Total = 14**

---

## ⏱️ Complexity

- **Time:** `O(n × k)`
- **Space:** `O(n × k × 3)`

---

## 🎯 Takeaway

This problem is a **three-state DP**:
- No position
- Holding stock
- Holding short

Once you see that, the rest is just disciplined state transitions.

---

