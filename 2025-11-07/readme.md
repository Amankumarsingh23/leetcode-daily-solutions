## 2528. Maximize the Minimum Powered City

**Difficulty:** Hard  
**Topic:** Binary Search, Greedy, Sliding Window  
**Company Tags:** LeetCode

---

### Problem Statement

You are given a 0-indexed integer array `stations` of length `n`, where `stations[i]`
represents the number of power stations in the `i`-th city.

Each power station provides power to all cities `j` such that:

|i - j| <= r


The **power of a city** is the total number of stations that provide power to it.

You are allowed to build **at most `k` additional power stations**, each having the same range `r`.

Return the **maximum possible minimum power** among all cities after optimally placing
the additional power stations.

---

### Key Idea

We want to **maximize the minimum power** across all cities.

This can be solved using **binary search on the answer**:

- Guess a minimum power `mid`
- Check if it's possible to make every city have at least `mid` power
- Use greedy placement of additional stations when needed

---

### Approach

1. Binary search on the minimum achievable power.
2. For a candidate power:
   - Use a sliding window to compute current city power.
   - If power is insufficient, greedily add stations at the farthest valid city.
3. If we exceed `k` additional stations, the candidate is invalid.

---

### C++ Solution

```cpp
class Solution {
 public:
  long long maxPower(vector<int>& stations, int r, int k) {
    long left = *min_element(stations.begin(), stations.end());
    long right = accumulate(stations.begin(), stations.end(), 0L) + k + 1;

    while (left < right) {
      long mid = (left + right) / 2;
      if (canAchieve(stations, r, k, mid))
        left = mid + 1;
      else
        right = mid;
    }

    return left - 1;
  }

 private:
  bool canAchieve(vector<int> stations, int r, int k, long minPower) {
    int n = stations.size();
    long currPower = 0;

    for (int i = 0; i < n; i++) {
      if (i + r < n)
        currPower += stations[i + r];

      if (currPower < minPower) {
        long need = minPower - currPower;
        if (need > k)
          return false;

        stations[min(n - 1, i + r)] += need;
        k -= need;
        currPower += need;
      }

      if (i - r >= 0)
        currPower -= stations[i - r];
    }

    return true;
  }
};

```
## Complexity Analysis

- Time Complexity: O(n log S)

where S is the total possible power.

- Space Complexity: O(n)

## Summary

- Binary search the answer

- Greedy placement of power stations

- Sliding window for efficient power calculation

- Optimal and scalable for large inputs