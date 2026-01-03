# 1411. Number of Ways to Paint N × 3 Grid

**Difficulty:** Hard  
**Topic:** Dynamic Programming

## Problem

You are given a grid of size `n × 3`. Each cell must be painted with exactly one of three colors:

- Red
- Yellow
- Green

No two adjacent cells (horizontal or vertical) can have the same color.

Return the number of valid ways to paint the grid.  
Since the answer can be large, return it modulo `10^9 + 7`.

## Observation

For a single row of 3 cells, valid colorings fall into exactly two patterns:

1. Type A (ABA): First and third cells have the same color, middle is different  
2. Type B (ABC): All three cells have different colors  

Number of ways for each type in one row:
- Type A = 6
- Type B = 6

## Dynamic Programming

Let:
- `a` = number of ways ending with Type A
- `b` = number of ways ending with Type B

Initial state (row 1):
- `a = 6`
- `b = 6`

Transitions:
- `newA = a * 3 + b * 2`
- `newB = a * 2 + b * 2`

Final answer:
- `(a + b) % MOD`

## C++ Solution

```cpp
class Solution {
public:
    static const int MOD = 1e9 + 7;

    int numOfWays(int n) {
        long long a = 6, b = 6;

        for (int i = 2; i <= n; i++) {
            long long newA = (a * 3 + b * 2) % MOD;
            long long newB = (a * 2 + b * 2) % MOD;
            a = newA;
            b = newB;
        }

        return (a + b) % MOD;
    }
};
```
Complexity

Time: O(n)

Space: O(1)
