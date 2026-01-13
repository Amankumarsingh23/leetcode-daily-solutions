# 3453. Separate Squares I

You are given a 2D integer array `squares`, where each element `squares[i] = [xi, yi, li]` represents a square with its bottom-left corner at `(xi, yi)` and side length `li`. All squares are aligned with the x-axis.

Your task is to find the minimum y-coordinate of a horizontal line such that the total area of all squares strictly above the line is equal to the total area of all squares strictly below the line. Squares may overlap, and overlapping areas must be counted multiple times. Answers within `1e-5` of the correct value are accepted.

The key observation is that if the total area of all squares is `T`, then we are looking for the smallest height `H` such that the area below the horizontal line `y = H` is at least `T / 2`.

For a single square `[x, y, l]`, its contribution to the area below height `H` is:
- `0` if `H <= y`
- `l * l` if `H >= y + l`
- `l * (H - y)` if `y < H < y + l`

Since the total area below `H` increases monotonically as `H` increases, we can apply binary search over the range of possible y-values.

---

## C++ Solution

```cpp
class Solution {
public:
    double separateSquares(vector<vector<int>>& squares) {
        double totalArea = 0.0;
        double low = 1e9, high = -1e9;

        // Compute total area and vertical bounds
        for (auto &s : squares) {
            double y = s[1];
            double l = s[2];
            totalArea += l * l;
            low = min(low, y);
            high = max(high, y + l);
        }

        double target = totalArea / 2.0;

        // Function to compute area below height H
        auto areaBelow = [&](double H) {
            double area = 0.0;
            for (auto &s : squares) {
                double y = s[1];
                double l = s[2];
                if (H <= y) continue;
                if (H >= y + l) area += l * l;
                else area += l * (H - y);
            }
            return area;
        };

        // Binary search for the answer
        for (int i = 0; i < 60; i++) {
            double mid = (low + high) / 2.0;
            if (areaBelow(mid) < target)
                low = mid;
            else
                high = mid;
        }

        return low;
    }
};
