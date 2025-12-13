# 🟦 3606. Coupon Code Validator  
**LeetCode — Easy | String Validation | Sorting**

---

## 📌 Problem Summary

You are given **three arrays** of length `n`:

- `code[i]` → coupon identifier (string)
- `businessLine[i]` → business category
- `isActive[i]` → whether the coupon is active

Each coupon `i` is **valid** if **all** of the following hold:

1. `code[i]` is **non-empty**
2. `code[i]` contains **only**:
   - lowercase letters (`a-z`)
   - uppercase letters (`A-Z`)
   - digits (`0-9`)
   - underscore (`_`)
3. `businessLine[i]` is one of:
   - `"electronics"`
   - `"grocery"`
   - `"pharmacy"`
   - `"restaurant"`
4. `isActive[i] == true`

---

electronics → grocery → pharmacy → restaurant

2. Then by `code` in **lexicographical (ascending) order** within the same business line.

---

## 🧠 Key Observations

### ✔️ Business Line Ordering Is Fixed  
We cannot sort alphabetically.  
Instead, we map each business line to a **rank**:

| Business Line | Rank |
|--------------|------|
| electronics  | 0 |
| grocery      | 1 |
| pharmacy     | 2 |
| restaurant   | 3 |

---

### ✔️ Code Validation Rules  
A valid code must:
- NOT be empty
- Contain **only** alphanumeric characters or `_`

We check each character using:
- `isalnum(c)` OR `c == '_'`

---

### ✔️ Sorting Strategy  
Store valid coupons as:

## 🎯 Goal

 (businessOrder, code)



Then sort by:
1. business order
2. code lexicographically

---

## 💻 C++ Solution (Clean & Efficient)

```cpp
class Solution {
public:
    vector<string> validateCoupons(vector<string>& code,
                                   vector<string>& businessLine,
                                   vector<bool>& isActive) {
        int n = code.size();

        // Fixed business order
        unordered_map<string, int> order = {
            {"electronics", 0},
            {"grocery", 1},
            {"pharmacy", 2},
            {"restaurant", 3}
        };

        vector<pair<int, string>> valid; // (businessOrder, code)

        for (int i = 0; i < n; i++) {
            // Must be active
            if (!isActive[i]) continue;

            // Must be a valid business line
            if (!order.count(businessLine[i])) continue;

            // Code must be non-empty
            if (code[i].empty()) continue;

            // Code must contain only [a-zA-Z0-9_]
            bool ok = true;
            for (char c : code[i]) {
                if (!isalnum(c) && c != '_') {
                    ok = false;
                    break;
                }
            }
            if (!ok) continue;

            valid.push_back({order[businessLine[i]], code[i]});
        }

        // Sort by business line order, then lexicographically by code
        sort(valid.begin(), valid.end(), [](auto &a, auto &b) {
            if (a.first != b.first)
                return a.first < b.first;
            return a.second < b.second;
        });

        // Extract only the codes
        vector<string> result;
        for (auto &p : valid) {
            result.push_back(p.second);
        }

        return result;
    }
};

```
| Metric | Value                                |
| ------ | ------------------------------------ |
| Time   | **O(n log n)** (due to sorting)      |
| Space  | **O(n)** (for storing valid coupons) |


## 📝 Notes

- Simple filter + custom sort problem

- Common interview pattern for:

- validation rules

- fixed-order sorting

- Clean usage of isalnum() for character checks
