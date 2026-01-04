# LeetCode 1390 — Four Divisors

**Difficulty:** Easy  
**Topic:** Math, Enumeration

## Problem

Given an integer array `nums`, return the sum of divisors of those integers that have exactly **four positive divisors**.  
If an integer does not have exactly four divisors, it contributes `0` to the sum.

## Key Insight

A number has **exactly four positive divisors** if and only if it is of one of the following forms:

1. `p³`, where `p` is a prime  
   Divisors: `{1, p, p², p³}`

2. `p × q`, where `p` and `q` are **distinct primes**  
   Divisors: `{1, p, q, p × q}`

## Efficient Strategy

For each number `x` in `nums`:

- Iterate divisors only up to `sqrt(x)`
- Count divisors and sum them
- Stop early if divisor count exceeds 4
- Add the sum only if divisor count is exactly 4

This avoids full factorization and is efficient for the constraints.

## C++ Solution

```cpp
class Solution {
public:
    int sumFourDivisors(vector<int>& nums) {
        int ans = 0;

        for (int x : nums) {
            int cnt = 0;
            int sum = 0;

            for (int d = 1; d * d <= x; d++) {
                if (x % d == 0) {
                    int e = x / d;
                    cnt++;
                    sum += d;

                    if (e != d) {
                        cnt++;
                        sum += e;
                    }

                    if (cnt > 4) break;
                }
            }

            if (cnt == 4) ans += sum;
        }

        return ans;
    }
};
