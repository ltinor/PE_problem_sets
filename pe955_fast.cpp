#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// Check if x is a triangle number: T_m = m(m+1)/2
// Returns m if triangle, -1 otherwise
ll is_triangle(i128 x) {
    // m(m+1)/2 = x => (2m+1)^2 = 8x+1
    i128 d = 8*x + 1;
    i128 s = (i128)sqrtl((long double)d);
    // Adjust
    while (s*s < d) s++;
    while (s*s > d) s--;
    if (s*s == d && (s - 1) % 2 == 0) {
        return (ll)((s - 1) / 2);
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    
    ll a = 3, d = 1, idx = 0;
    int tri_count = 1;  // a_0 = 3 is T_2
    
    ll target = 70;
    ll prev_tri_idx = 0;
    
    while (tri_count < target) {
        if (is_triangle(a) >= 0) {
            d = 1;
        } else {
            d++;
        }
        a += d;
        idx++;
        
        if (is_triangle(a) >= 0) {
            tri_count++;
            if (tri_count <= 20 || tri_count % 10 == 0) {
                cerr << "  #" << tri_count << ": a_" << idx << " = " << a << " (diff=" << (idx - prev_tri_idx) << ")" << endl;
            }
            prev_tri_idx = idx;
        }
    }
    
    cout << "70th triangle number: a_" << idx << " = " << a << endl;
    return 0;
}
