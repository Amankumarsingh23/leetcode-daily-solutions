# 2211. Count Collisions on a Road

Language: C++
Solution file: 2211_count_collisions_on_a_road.cpp

## 📝 Summary

You’re given a road with n cars, each either:

    'L' → moving left
    
    'R' → moving right
    
    'S' → stationary
    
    All moving cars have equal speed.
    
    Collisions happen when:
    
    R meets L → +2 collisions (both freeze)
    
    R meets S → +1 collision (R freezes)
    
    L meets S → +1 collision (L freezes)
    
    After collision, cars stop forever.
    
    The goal is to return total collisions.

## 💡 Intuition

Most cars at the far ends never collide:

Cars starting with 'L' at the left end move left forever → no collision

Cars ending with 'R' at the right end move right forever → no collision

Remove them.

Inside the middle region:
Any 'R' or 'L' that remains must collide eventually.

Why?
Because:

A left-moving car inside the middle will eventually hit something to its left (not an infinite road anymore).

A right-moving car inside the middle will eventually hit something to its right.

So the number of collisions =
👉 Number of non-'S' cars in the middle region

🧠 Approach
Step 1 — Remove non-colliding cars

Skip all leading 'L'

Skip all trailing 'R'

Step 2 — Count all 'L' and 'R' inside

Each such car will certainly collide, giving exactly +1 collision each.

## 🔥 Complexity

Time: O(n)

Space: O(1)

Fastest possible.

## 🧾 Code (C++)


    class Solution {
    public:
        int countCollisions(string s) {

        int n = s.size();
        int i = 0, j = n - 1;

        // Remove leading L
        while (i < n && s[i] == 'L') i++;

        // Remove trailing R
        while (j >= 0 && s[j] == 'R') j--;

        int ans = 0;

        // Count moving cars in the middle region
        for (int k = i; k <= j; k++) {
            if (s[k] != 'S')
                ans++;
        }

        return ans;
    }
    };

## 📌 Final Notes

Leading 'L' and trailing 'R' can't collide → ignore them

Every remaining 'L' or 'R' must collide, hence simply counted

'S' never causes collisions but can stop a moving car

This optimal logic avoids simulations entirely
