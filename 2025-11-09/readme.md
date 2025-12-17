# 🟦 2169. Count Operations to Obtain Zero

✔️ LeetCode — Easy

✔️ Simulation / Greedy

✔️ C++ Clean Solution

## 📌 Problem Summary

You are given two non-negative integers num1 and num2.

In one operation:

- If **num1 ≥ num2 ** → subtract num2 from num1

- Else → subtract num1 from num2

Continue performing operations **until either number becomes 0**.

## 🎯 Goal

Return the total number of operations required to make either num1 or num2 equal to 0.

## 🧠 Key Insight

This problem is a direct simulation of repeated subtraction:

Each operation strictly reduces one of the numbers

The process always terminates

Count how many steps it takes

This is essentially a slow version of the Euclidean Algorithm (without division).

## 🔍 Example

Input

num1 = 2, num2 = 3


Operations

2 < 3 → num2 = 3 - 2 = 1

2 > 1 → num1 = 2 - 1 = 1

1 = 1 → num1 = 1 - 1 = 0

✅ Total operations = 3

## 💻 C++ Implementation (Clean & Simple)
    #include <bits/stdc++.h>
    using namespace std;
    
    class Solution {
    public:
        int countOperations(int num1, int num2) {
            int count = 0;
    
            while (num1 > 0 && num2 > 0) {
                if (num1 >= num2) {
                    num1 -= num2;
                } else {
                    num2 -= num1;
                }
                count++;
            }
    
            return count;
        }
    };

## ⏱️ Complexity Analysis

Time Complexity: O(num1 + num2) (worst case)

Space Complexity: O(1)

## ✅ Final Notes

No edge cases missed

Works for all non-negative inputs

Fully GitHub-safe Markdown

Clean formatting, no broken sections
