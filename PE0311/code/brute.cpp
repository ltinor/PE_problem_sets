#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Brute force for small N: enumerate all quadruples directly
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    ll max_side = (ll)sqrt((double)N / 2) + 1;
    ll ans = 0;

    for (ll a = 1; a <= max_side; a++) {
        for (ll b = a + 1; b <= max_side; b++) {
            for (ll c = b + 1; c <= max_side; c++) {
                for (ll d = c + 1; d <= max_side; d++) {
                    if (a*a + b*b + c*c + d*d > N) break;
                    if (a*a + d*d != b*b + c*c) continue;
                    ll S = a*a + d*d;
                    if (S % 2 != 0) continue;
                    ll T = S / 2;

                    for (ll k = (ll)sqrt((double)T/2); k*k <= T; k++) {
                        ll AO2 = T - k*k;
                        ll AO = (ll)sqrt((double)AO2);
                        if (AO*AO != AO2 || AO > k) continue;
                        
                        ll BD = 2*k, BD2 = BD*BD;
                        
                        ll num_xA = a*a + BD2 - d*d;
                        if (num_xA % (2*BD)) continue;
                        ll xA = num_xA / (2*BD);
                        ll yA2 = a*a - xA*xA;
                        if (yA2 <= 0) continue;
                        ll yA = (ll)sqrt((double)yA2);
                        if (yA*yA != yA2) continue;

                        ll num_xC = b*b + BD2 - c*c;
                        if (num_xC % (2*BD)) continue;
                        ll xC = num_xC / (2*BD);
                        ll yC2 = b*b - xC*xC;
                        if (yC2 <= 0) continue;
                        ll yC = (ll)sqrt((double)yC2);
                        if (yC*yC != yC2) continue;

                        if (yA * yC >= 0) continue;
                        if (xA < 0 || xA > BD || xC < 0 || xC > BD) continue;

                        ans++;
                    }
                }
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
