# 🧭 LeetCode 2435 — Paths in Matrix Whose Sum Is Divisible by K

Difficulty: Hard
Tags: Dynamic Programming, Grid, Modulo, 3D DP

## 📝 Problem Summary

You are given an m × n grid and an integer k.
You start at (0, 0) and must reach (m-1, n-1) by moving only right or down.

A path is valid if:

The sum of all values on the path is divisible by k

Return the number of such valid paths mod 1e9+7.

## 💡 Core Idea — 3D Dynamic Programming (DP)

Define a DP state:
        
        dp[i][j][r] = number of ways to reach cell (i, j)
                     with path sum modulo k equal to r


Transitions:

From top (i-1, j) or left (i, j-1):

        new_r = (old_r + grid[i][j]) % k
        dp[i][j][new_r] += dp[prev][old_r]


Initialize:

        dp[0][0][grid[0][0] % k] = 1


Final answer:

        dp[m-1][n-1][0]


Because remainder 0 ⇒ sum divisible by k.

## 🕒 Complexity

Time: O(m × n × k)

Space: O(m × n × k)

## ✅ C++ Code (Final, Clean, Fully Working)


   
    
          class Solution {
      public:
          static const int MOD = 1e9 + 7;
                    int numberOfPaths(vector<vector<int>>& grid, int k) {
                  int m = grid.size(), n = grid[0].size();
          
                  // dp[i][j][r] = number of paths to reach (i, j) with sum % k = r
                  vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(k, 0)));
          
                  dp[0][0][grid[0][0] % k] = 1;
          
                  for (int i = 0; i < m; i++) {
                      for (int j = 0; j < n; j++) {
                          int val = grid[i][j];
          
                          for (int r = 0; r < k; r++) {
                              // from top
                              if (i > 0) {
                                  int new_r = (r + val) % k;
                                  dp[i][j][new_r] = (dp[i][j][new_r] + dp[i - 1][j][r]) % MOD;
                              }
                              // from left
                              if (j > 0) {
                                  int new_r = (r + val) % k;
                                  dp[i][j][new_r] = (dp[i][j][new_r] + dp[i][j - 1][r]) % MOD;
                              }
                          }
                      }
                  }
          
                  return dp[m - 1][n - 1][0]; // remainder 0 => divisible
              }};

## 📌 Notes

This is a classic grid DP with modulo states

The 3D state ensures we track possible remainders along each path

Efficient and fully fits constraints
