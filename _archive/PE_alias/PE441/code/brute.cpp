#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

// PE441 brute: direct triple loop for verification (very small N only)
// R(M) = sum_{1≤p<q≤M, p+q≥M, gcd(p,q)=1} 1/(p·q)

ll my_gcd(ll a, ll b) { return b ? my_gcd(b, a % b) : a; }

ld S_direct(int N) {
    ld ans = 0;
    for (int M = 2; M <= N; M++) {
        for (int p = 1; p <= M; p++) {
            for (int q = p+1; q <= M; q++) {
                if (p + q < M) continue;
                if (my_gcd(p, q) != 1) continue;
                ans += 1.0L / ((ld)p * q);
            }
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cout << fixed << setprecision(4);
    int N; cin >> N;
    cout << S_direct(N) << "\n";
}
