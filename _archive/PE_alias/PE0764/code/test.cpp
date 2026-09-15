#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

i64 gcd(i64 a, i64 b) { return b ? gcd(b, a%b) : a; }

// Compute S(N) for verification
i64 S(i64 N) {
    i64 ans = 0;
    i64 max_v = (i64)pow(2.0 * N, 0.25) + 2;
    
    // Case g=1: a=u^4, b=v^4, gcd(u,v)=1
    for (i64 v = 1; v <= max_v; v++) {
        i64 v4 = v*v*v*v;
        if (v4 > 2*N) break;
        for (i64 u = 1; u < v; u++) {
            if (gcd(u,v) != 1) continue;
            i64 u4 = u*u*u*u;
            i64 diff = v4 - u4;
            if (diff % 8 != 0) continue;
            i64 x = diff / 8;
            if (x <= 0 || x > N) continue;
            i64 y = u * v;
            if (y > N) continue;
            i64 z = (u4 + v4) / 2;
            if (z > N) continue;
            if (gcd(gcd(x,y),z) != 1) continue;
            ans += x + y + z;
        }
    }
    return ans;
}

int main() {
    cout << "S(100) = " << S(100) << " (expected 81)" << endl;
    cout << "S(10000) = " << S(10000) << " (expected 112851)" << endl;
    return 0;
}
