#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll count_grid(int W, int H) {
    // Normal rectangles: C(W+1,2) * C(H+1,2)
    ll normal = (ll)W*(W+1)/2 * (ll)H*(H+1)/2;
    
    // Cross-hatched rectangles from diagonal intersections
    // Grid has (W+1) vertical lines, (H+1) horizontal lines
    // Choose 2 NW-SE diagonals and 2 NE-SW diagonals where intersections are in bounds
    int K = W + H + 1; // number of diagonals in each direction
    ll cross = 0;
    
    // Precompute for each pair of NW-SE lines (k1<k2): width = (k2-k1)/2 needs to be int
    for (int k1 = 0; k1 < K; k1++) {
        for (int k2 = k1 + 2; k2 < K; k2 += 2) {
            int dw = (k2 - k1) / 2; // half the horizontal distance
            // For each pair of NE-SW lines (l1<l2): height = (l2-l1)/2
            for (int l1 = 0; l1 < K; l1++) {
                for (int l2 = l1 + 2; l2 < K; l2 += 2) {
                    int dh = (l2 - l1) / 2;
                    // 4 corners: (x,y) where x = (k-l+W)/2? 
                    // The intersections are at specific grid positions
                    // Intersection of NW-SE line k and NE-SW line l:
                    // x = (l - k + W) / 2, y = (k + l - W) / 2
                    // All 4 corners must have 0<=x<=W and 0<=y<=H
                    
                    auto in_bounds = [&](int k, int l) {
                        int x = l - k + W;
                        int y = k + l - W;
                        return (x>=0 && x<=2*W && y>=0 && y<=2*H && x%2==0 && y%2==0);
                    };
                    
                    if (in_bounds(k1,l1) && in_bounds(k1,l2) && in_bounds(k2,l1) && in_bounds(k2,l2))
                        cross++;
                }
            }
        }
    }
    
    return normal + cross;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int W, H; cin >> W >> H;
    ll ans = 0;
    for (int w = 1; w <= W; w++)
        for (int h = 1; h <= H; h++)
            ans += count_grid(w, h);
    cout << ans << "\n";
}
