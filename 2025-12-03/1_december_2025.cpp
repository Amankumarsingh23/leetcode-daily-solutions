#include <vector>
#include <unordered_map>
#include <map>
#include <utility>
#include <functional>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

class Fraction {
public:
    long long num, den;
    
    Fraction(long long n = 0, long long d = 1) : num(n), den(d) {
        normalize();
    }
    
    void normalize() {
        if (den == 0) {
            num = 1; // Represent infinity
            den = 0;
            return;
        }
        
        if (den < 0) {
            num = -num;
            den = -den;
        }
        
        long long g = gcd(abs(num), den);
        num /= g;
        den /= g;
    }
    
    bool operator==(const Fraction& other) const {
        return num == other.num && den == other.den;
    }
    
    bool operator<(const Fraction& other) const {
        if (den == 0 && other.den == 0) return false;
        if (den == 0) return false;
        if (other.den == 0) return true;
        return num * other.den < other.num * den;
    }
    
private:
    long long gcd(long long a, long long b) {
        while (b != 0) {
            long long temp = a % b;
            a = b;
            b = temp;
        }
        return a;
    }
};

struct FractionHash {
    size_t operator()(const Fraction& f) const {
        return hash<long long>()(f.num) ^ (hash<long long>()(f.den) << 1);
    }
};

struct FractionEqual {
    bool operator()(const Fraction& a, const Fraction& b) const {
        return a.num == b.num && a.den == b.den;
    }
};

class Solution {
public:
    int countTrapezoids(vector<vector<int>>& points) {
        int n = points.size();
        
        unordered_map<Fraction, vector<Fraction>, FractionHash, FractionEqual> slope_to_intercepts;
        map<pair<long long, long long>, vector<Fraction>> midpoint_to_slopes;
        
        for (int i = 0; i < n; i++) {
            int x1 = points[i][0], y1 = points[i][1];
            for (int j = i + 1; j < n; j++) {
                int x2 = points[j][0], y2 = points[j][1];
                int dx = x2 - x1, dy = y2 - y1;
                
                Fraction slope, intercept;
                
                if (dx != 0) {
                    slope = Fraction(dy, dx);
                    intercept = Fraction((long long)y1 * dx - (long long)dy * x1, dx);
                } else {
                    slope = Fraction(1, 0);
                    intercept = Fraction(x1, 1);
                }
                
                slope_to_intercepts[slope].push_back(intercept);
                
                long long mid_x = (long long)x1 + x2;
                long long mid_y = (long long)y1 + y2;
                midpoint_to_slopes[{mid_x, mid_y}].push_back(slope);
            }
        }
        
        long long res = 0;
        
        for (auto& [slope, intercepts] : slope_to_intercepts) {
            if (intercepts.size() < 2) continue;
            
            unordered_map<Fraction, int, FractionHash, FractionEqual> intercept_count;
            for (auto& intercept : intercepts) {
                intercept_count[intercept]++;
            }
            
            long long total_lines = intercepts.size();
            long long total_pairs = total_lines * (total_lines - 1) / 2;
            long long same_intercept_pairs = 0;
            
            for (auto& [intercept, count] : intercept_count) {
                if (count > 1) {
                    same_intercept_pairs += (long long)count * (count - 1) / 2;
                }
            }
            
            res += total_pairs - same_intercept_pairs;
        }
        
        for (auto& [midpoint, slopes] : midpoint_to_slopes) {
            if (slopes.size() < 2) continue;
            
            unordered_map<Fraction, int, FractionHash, FractionEqual> slope_count;
            for (auto& slope : slopes) {
                slope_count[slope]++;
            }
            
            long long acc = 0;
            for (auto& [slope, count] : slope_count) {
                res -= acc * count;
                acc += count;
            }
        }
        
        return (int)res;
    }
};
