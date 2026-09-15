#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    ll max_S = N / 2;
    ll max_side = (ll)sqrt((double)max_S) + 1;

    vector<vector<pair<ll,ll>>> pairs_by_S(max_S + 1);
    for (ll x = 1; x <= max_side; x++) {
        ll xx = x * x;
        for (ll y = x + 1; y <= max_side; y++) {
            ll S = xx + y * y;
            if (S > max_S) break;
            pairs_by_S[S].push_back({x, y});
        }
    }

    ll ans = 0;

    for (ll S = 2; S <= max_S; S += 2) {
        auto& pairs = pairs_by_S[S];
        int sz = pairs.size();
        if (sz < 2) continue;

        ll T = S / 2;

        for (int i = 0; i < sz; i++) {
            ll a = pairs[i].first, d = pairs[i].second;
            for (int j = i + 1; j < sz; j++) {
                ll b = pairs[j].first, c = pairs[j].second;
                
                vector<ll> sides = {a, d, b, c};
                sort(sides.begin(), sides.end());
                ll A = sides[0], B = sides[1], C = sides[2], D = sides[3];
                
                if (A*A + D*D != S) continue;
                if (B*B + C*C != S) continue;

                // Triangle inequalities: |A-D| < BD < A+D, |B-C| < BD < B+C
                ll BD_min = D - A + 1; // BD > D - A
                ll BD_max = A + D - 1; // BD < A + D
                BD_min = max(BD_min, C - B + 1);
                BD_max = min(BD_max, B + C - 1);
                
                // BD must be even
                if (BD_min % 2 != 0) BD_min++;
                if (BD_max % 2 != 0) BD_max--;
                if (BD_min > BD_max) continue;

                for (ll BD = BD_min; BD <= BD_max; BD += 2) {
                    ll k = BD / 2;
                    ll AO2 = T - k * k;
                    if (AO2 <= 0) continue;
                    ll AO = (ll)sqrt((double)AO2);
                    if (AO * AO != AO2) continue;
                    if (AO > k) continue;

                    ans++;
                }
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
