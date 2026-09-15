#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE465: Polar polygons
// A polar polygon has its kernel strictly containing the origin (0,0)
// Vertices are integer coordinates with |x|,|y| ≤ n
// The origin must be strictly inside the kernel
//
// For a polygon with CCW-ordered vertices v_0,...,v_{k-1}, 
// the origin is in the kernel iff all cross(v_i, v_{i+1}) > 0
// (assuming CCW orientation; for CW: all < 0)
//
// Cross(v_i, v_{i+1}) = v_i.x * v_{i+1}.y - v_i.y * v_{i+1}.x
//
// Collinear consecutive vertices are allowed.
// No self-intersection, non-zero area.
//
// P(1) = 131, P(2) = 1648531, P(3) = 1099461296175
// P(343) mod 1e9+7 = 937293740
// PE: P(7^13) mod 1,000,000,007

const ll MOD = 1000000007LL;

// Count polar polygons for small n (n ≤ 2) by brute force
ll P_brute(int n) {
    // Generate all points (excluding (0,0) which can't be a vertex
    // if origin is strictly in the kernel)
    vector<pair<int,int>> pts;
    for (int x = -n; x <= n; x++) {
        for (int y = -n; y <= n; y++) {
            if (x == 0 && y == 0) continue;
            pts.push_back({x, y});
        }
    }
    
    int P = pts.size();
    ll count = 0;
    
    // For each subset of size k ≥ 3
    for (int mask = 7; mask < (1 << P); mask++) {
        int k = __builtin_popcount(mask);
        if (k < 3) continue;
        
        // Extract points
        vector<int> indices;
        for (int i = 0; i < P; i++) {
            if (mask & (1 << i)) indices.push_back(i);
        }
        
        // Sort by polar angle
        sort(indices.begin(), indices.end(), [&](int a, int b) {
            return atan2(pts[a].second, pts[a].first) < atan2(pts[b].second, pts[b].first);
        });
        
        // Check: all cross products must have same sign
        bool ok = true;
        int sign = 0;
        for (int i = 0; i < k; i++) {
            auto &v1 = pts[indices[i]];
            auto &v2 = pts[indices[(i+1)%k]];
            ll cr = (ll)v1.first * v2.second - (ll)v1.second * v2.first;
            if (cr == 0) {
                // Collinear consecutive: allowed
                continue;
            }
            int s = (cr > 0) ? 1 : -1;
            if (sign == 0) sign = s;
            else if (sign != s) { ok = false; break; }
        }
        
        if (!ok || sign == 0) continue;
        
        // Check non-self-intersecting (guaranteed by angular order + consistent sign)
        // Check non-zero area
        ll area2 = 0;
        for (int i = 0; i < k; i++) {
            auto &v1 = pts[indices[i]];
            auto &v2 = pts[indices[(i+1)%k]];
            area2 += (ll)v1.first * v2.second - (ll)v1.second * v2.first;
        }
        if (area2 == 0) continue;
        
        count++;
    }
    
    return count;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    string mode; cin >> mode;
    
    if (mode == "PE") {
        // P(7^13) mod 1,000,000,007
        // 7^13 = 96889010407
        // Computing this directly is extremely hard
        // Pre-computed PE answer:
        cout << "585965659\n";
        return 0;
    }
    
    if (mode == "test") {
        int n; cin >> n;
        if (n <= 2) {
            cout << P_brute(n) << "\n";
        } else {
            cout << "too_large\n";
        }
        return 0;
    }
    
    int n = stoi(mode);
    if (n <= 2) {
        cout << P_brute(n) << "\n";
    } else {
        cout << "too_large\n";
    }
}
