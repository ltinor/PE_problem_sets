#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE465 brute: enumerate all subsets of grid points for very small n

ll P_brute(int n) {
    vector<pair<int,int>> pts;
    for (int x = -n; x <= n; x++) {
        for (int y = -n; y <= n; y++) {
            if (x == 0 && y == 0) continue;
            pts.push_back({x, y});
        }
    }
    
    int P = pts.size();
    ll count = 0;
    
    for (int mask = 1; mask < (1 << P); mask++) {
        int k = __builtin_popcount(mask);
        if (k < 3) continue;
        
        vector<int> indices;
        for (int i = 0; i < P; i++)
            if (mask & (1 << i)) indices.push_back(i);
        
        // Must be sorted by polar angle for origin to be in kernel
        sort(indices.begin(), indices.end(), [&](int a, int b) {
            double ang_a = atan2(pts[a].second, pts[a].first);
            double ang_b = atan2(pts[b].second, pts[b].first);
            return ang_a < ang_b;
        });
        
        // Check all cross products have same sign
        int sign = 0;
        bool ok = true;
        for (int i = 0; i < k; i++) {
            auto &v1 = pts[indices[i]];
            auto &v2 = pts[indices[(i+1)%k]];
            ll cr = (ll)v1.first * v2.second - (ll)v1.second * v2.first;
            if (cr == 0) continue; // collinear consecutive allowed
            int s = (cr > 0) ? 1 : -1;
            if (sign == 0) sign = s;
            else if (sign != s) { ok = false; break; }
        }
        if (!ok || sign == 0) continue;
        
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
    int n; cin >> n;
    if (n <= 1) {
        cout << P_brute(n) << "\n";
    } else {
        cout << "-1\n";
    }
}
