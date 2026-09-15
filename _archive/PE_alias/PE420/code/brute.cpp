#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE420 brute: count matrices with 2+ square representations

ll F_brute(ll N) {
    map<tuple<ll,ll,ll,ll>, int> cnt;
    ll lim_ad = (ll)sqrt(N) + 1;
    for (ll a = 1; a <= lim_ad; a++) {
        for (ll d = 1; d <= lim_ad; d++) {
            ll rem = N - a*a - d*d;
            if (rem <= 2) continue;
            ll max_b = (rem - 1) / 2;
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
    cout << F_brute(N) << "\n";
}
