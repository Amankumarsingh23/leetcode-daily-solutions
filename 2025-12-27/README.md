# 2402. Meeting Rooms III (Hard)

This problem is all about priority queues + careful simulation.

## 🧠 Core Idea (Very Important)

- We need to simulate meetings in order of start time and always:

- Use the smallest numbered available room

- If no room is free → delay the meeting

## Delayed meeting:

- Starts when the earliest room becomes free

- Keeps the same duration

- If multiple meetings are waiting, the one with earlier original start gets priority (sorting already handles this)

## 🏗 Data Structures Used

### 1️⃣ Available Rooms (min room number)

    priority_queue<int, vector<int>, greater<int>> freeRooms;

### 2️⃣ Occupied Rooms (earliest ending first)

    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<>> busy;


    Stores {endTime, roomNumber}

### 3️⃣ Count meetings per room

    vector<int> count(n, 0);

## 🚀 Algorithm Steps

- Sort meetings by start

- Initialize all rooms as free

### For each meeting:

- Free rooms whose meetings have ended

- If a room is available → assign immediately

- Else → delay until earliest room frees

- Track usage count

- Return room with max meetings (tie → smallest index)

## ✅ C++ Solution (Optimal)
```

class Solution {
public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
        sort(meetings.begin(), meetings.end());

        priority_queue<int, vector<int>, greater<int>> freeRooms;
        priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<>> busy;

        for (int i = 0; i < n; i++) freeRooms.push(i);

        vector<int> cnt(n, 0);

        for (auto &m : meetings) {
            long long start = m[0], end = m[1];
            long long duration = end - start;

            // Free rooms that are done
            while (!busy.empty() && busy.top().first <= start) {
                freeRooms.push(busy.top().second);
                busy.pop();
            }

            if (!freeRooms.empty()) {
                int room = freeRooms.top(); freeRooms.pop();
                busy.push({end, room});
                cnt[room]++;
            } else {
                auto [t, room] = busy.top();
                busy.pop();
                busy.push({t + duration, room});
                cnt[room]++;
            }
        }

        int ans = 0;
        for (int i = 1; i < n; i++) {
            if (cnt[i] > cnt[ans]) ans = i;
        }
        return ans;
    }
};
```

## ⏱ Complexity

| Metric | Value          |
| ------ | -------------- |
| Time   | **O(m log n)** |
| Space  | **O(n)**       |


   Where m = meetings.size()

## ⚠️ Common Mistakes (Cause of WA / TLE)

- ❌ Not sorting meetings
- ❌ Using queue instead of priority queue
- ❌ Forgetting to delay meetings correctly
- ❌ Updating end time incorrectly
- ❌ Not using long long for time
