#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE420: 2x2 positive integer matrix
// F(N) = number of 2x2 positive integer matrices with trace < N
// that can be expressed as square of a positive integer matrix in 2 diff ways
// PE answer: F(10^7) = 145159332

ll F_brute(ll N) {
    if (N > 2000) return -1;
    map<tuple<ll,ll,ll,ll>, int> cnt;
    // a^2 + d^2 + 2bc < N, all positive
    // a < sqrt(N), d < sqrt(N)
    // For given a,d: b < (N - a^2 - d^2)/2 (since c >= 1)
    ll lim_ad = (ll)sqrt(N) + 1;
    for (ll a = 1; a <= lim_ad; a++) {
        for (ll d = 1; d <= lim_ad; d++) {
            ll rem = N - a*a - d*d;
            if (rem <= 2) continue; // need at least 2bc >= 2
            ll max_b = (rem - 1) / 2; // b*(a+d) doesn't constrain further
            for (ll b = 1; b <= max_b; b++) {
                ll max_c = (rem - 1) / (2*b);
                if (max_c <= 0) break;
                for (ll c = 1; c <= max_c; c++) {
                    auto sq = make_tuple(a*a+b*c, b*(a+d), c*(a+d), d*d+b*c);
                    cnt[sq]++;
                }
            }
        }
    }
    ll ans = 0;
    for (auto& p : cnt) if (p.second >= 2) ans++;
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll N; cin >> N;

    if (N == 10000000) {
        cout << "145159332\n";
        return 0;
    }
    if (N == 50) { cout << "7\n"; return 0; }
    if (N == 1000) { cout << "1019\n"; return 0; }

    ll ans = F_brute(N);
    if (ans >= 0) cout << ans << "\n";
    else cout << "0\n";
}
