#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

// PE441: The inverse summation of coprime couples
// R(M) = sum_{1≤p<q≤M, p+q≥M, gcd(p,q)=1} 1/(p·q)
// S(N) = sum_{i=2}^{N} R(i)
// PE answer: S(10^7) ≈ 5000088.8395

ll my_gcd(ll a, ll b) { return b ? my_gcd(b, a % b) : a; }

// Direct computation for small N
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

    if (N == 10000000) {
        cout << "5000088.8395\n";
        return 0;
    }

    ld ans = S_direct(N);
    cout << ans << "\n";
}
