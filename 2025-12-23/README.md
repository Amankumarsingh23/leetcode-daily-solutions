# 2054. Two Best Non-Overlapping Events

**Difficulty:** Medium  
**Topics:** Greedy, Binary Search, Sorting  
**Companies:** Premium

---

## Problem

You are given a 0-indexed 2D integer array `events` where:

- `events[i] = [startTime_i, endTime_i, value_i]`
- The event starts at `startTime_i` and ends at `endTime_i`
- Attending the event gives `value_i`

You may attend **at most two non-overlapping events** such that the **sum of their values is maximized**.

### Non-overlapping rule
If an event ends at time `t`, the next event must start at **`t + 1` or later**.

---

## Return

Return the **maximum possible sum of values**.

---

## Example


Input: events = [[1,3,2],[4,5,2],[2,4,3]]

Output: 4


---

## Approach

1. Sort events by start time.
2. Build a suffix array to track the maximum value from the right.
3. For each event:
   - Consider it alone.
   - Use binary search to find the next non-overlapping event.
   - Combine their values.
4. Track the maximum result.

---

## Solution (C++)

```cpp
class Solution {
public:
    int maxTwoEvents(vector<vector<int>>& events) {
        int n = events.size();

        // Sort events by start time
        sort(events.begin(), events.end());

        // Suffix max array of event values
        vector<int> suffixMax(n);
        suffixMax[n - 1] = events[n - 1][2];
        for (int i = n - 2; i >= 0; i--) {
            suffixMax[i] = max(suffixMax[i + 1], events[i][2]);
        }

        int ans = 0;

        for (int i = 0; i < n; i++) {
            // Single event case
            ans = max(ans, events[i][2]);

            // Binary search for next non-overlapping event
            int lo = i + 1, hi = n - 1;
            int next = -1;

            while (lo <= hi) {
                int mid = (lo + hi) / 2;
                if (events[mid][0] >= events[i][1] + 1) {
                    next = mid;
                    hi = mid - 1;
                } else {
                    lo = mid + 1;
                }
            }

            if (next != -1) {
                ans = max(ans, events[i][2] + suffixMax[next]);
            }
        }

        return ans;
    }
};
```
## ⏱ Complexity

| Metric | Value          |
| ------ | -------------- |
| Time   | **O(n log n)** |
| Space  | **O(n)**       |
