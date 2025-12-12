# 🟦 3433. Count Mentions Per User  
**LeetCode — Medium | Simulation | Events Processing**

---

## 📌 Problem Summary

You are given:

- `numberOfUsers` → total number of users (IDs: 0 … numberOfUsers-1)  
- `events` → a list of events; each event is one of:

### **1️⃣ MESSAGE Event**

["MESSAGE", timestamp, mentions_string]

The message may include:
- `id<number>` → mentions that specific user (duplicates allowed)
- `ALL` → mentions *every user*
- `HERE` → mentions *every online user*

### **2️⃣ OFFLINE Event**

The message may include:
- `id<number>` → mentions that specific user (duplicates allowed)
- `ALL` → mentions *every user*
- `HERE` → mentions *every online user*

### **2️⃣ OFFLINE Event**

["OFFLINE", timestamp, id]

The user becomes **offline for 60 units**, then automatically back online.

### 📝 Important Rules
- All users **start online**
- If multiple events share a timestamp:
  - **ONLINE/OFFLINE changes are processed FIRST**, then MESSAGE events
- A user can be mentioned multiple times in a single message → count all occurrences
- Output: mentions[i] = total times user i was mentioned


---

## 🧠 Key Observations

### ✔️ 1. Events must be processed in **sorted timestamp order**

If timestamps tie:
- OFFLINE should be processed before MESSAGE  
Solution uses:  
```cpp
return a[0][2] < b[0][2];
```
which sorts "OFFLINE" before "MESSAGE" because 'F' < 'S'.

### ✔️ 2. Track Offline Windows

onlineT[i] = time until user i stays offline

A user i is online at time cur iff:

    onlineT[i] <= curr
### ✔️ 3. Mentions Types Logic
  Mention Type	Action
  
  ALL	Everyone gets +1
  
  HERE	Only currently online users get +1
  
  "id<num>"	That specific user gets +1
  
  Offline Event	mark user as offline until timestamp + 60

# 💻 Clean & Fully Explained C++ Solution

    class Solution {
    public:
        vector<int> countMentions(int numberOfUsers, vector<vector<string>>& events) {
            // Sort events by timestamp, and ensure OFFLINE comes before MESSAGE if tied
            ranges::sort(events, [](const vector<string>& a, const vector<string>& b) {
                int x = stoi(a[1]);
                int y = stoi(b[1]);
                if (x == y) {
                    return a[0][2] < b[0][2]; // OFFLINE ('F') < MESSAGE ('S')
                }
                return x < y;
            });

        vector<int> ans(numberOfUsers, 0);
        vector<int> onlineT(numberOfUsers, 0);  // used to track offline-until time
        int lazy = 0;  // count of how many ALL events occurred

        for (const auto& e : events) {
            string etype = e[0];
            int cur = stoi(e[1]);
            string s = e[2];

            if (etype[0] == 'O') {  
                // OFFLINE event
                onlineT[stoi(s)] = cur + 60;

            } else if (s[0] == 'A') {  
                // ALL
                lazy++;

            } else if (s[0] == 'H') {  
                // HERE → all online users at time cur
                for (int i = 0; i < numberOfUsers; ++i) {
                    if (onlineT[i] <= cur) {
                        ++ans[i];
                    }
                }

            } else {
                // id<number> tokens → individual mentions
                stringstream ss(s);
                string token;
                while (ss >> token) {
                    ans[stoi(token.substr(2))]++;
                }
            }
        }

        // Apply ALL mentions at the very end
        if (lazy > 0) {
            for (int i = 0; i < numberOfUsers; ++i) {
                ans[i] += lazy;
            }
        }

        return ans;
    }
    };


# ✅ Complexity
    Operation	Complexity
    
    Sorting events	O(n log n)
    
    Processing each event	O(n_users) worst case (for HERE)
    
    Total worst-case	O(n log n + n × numberOfUsers)


