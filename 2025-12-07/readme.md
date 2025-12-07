# 🔢 LeetCode 1523 — Count Odd Numbers in an Interval Range

Difficulty: Easy
Tags: Math, Counting

## 📝 Problem Summary

You are given two integers low and high.

Your task:

    Count how many odd numbers lie between low and high (inclusive).

Example:

Input: low = 3, high = 7

Odds: [3, 5, 7] → 3 numbers

## 💡 Core Idea — Count Odds Mathematically

Instead of iterating through the range, use a simple formula:

Key Insight

Count of odds from 0 to x is:

    (x + 1) / 2


So the count of odds in [low, high] is:

    odds(high) - odds(low - 1)


Which simplifies to:

    (high + 1) / 2 - (low) / 2


This is O(1) and super clean.

## 🕒 Complexity

Time: O(1)

Space: O(1)

## ✅ C++ Code (Final, Clean, Fully Working)

    class Solution {
    public:
        int countOdds(int low, int high) {
            return (high + 1) / 2 - low / 2;
        }
    };

## 📌 Notes

Pure math, no loops needed

Works for all valid integer ranges

Extremely efficient
