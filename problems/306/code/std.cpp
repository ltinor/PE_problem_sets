#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    // Dawson's Kayles: compute Grundy numbers with period detection
    // Period 34, starting at n=52 (preperiod 0..51)
    const int PRE = 200;  // compute more than enough for detection
    vector<int> g(PRE + 34, 0);  // extra space for period detection

    // g[0] = 0, g[1] = 0
    for (int n = 2; n < PRE + 34; n++) {
        set<int> s;
        for (int i = 0; i <= n - 2; i++) {
            s.insert(g[i] ^ g[n - i - 2]);
        }
        int mex = 0;
        while (s.count(mex)) mex++;
        g[n] = mex;
    }

    // Detect period: find repeat of length 34
    int period_start = -1;
    const int PERIOD_LEN = 34;
    for (int start = 0; start + 2 * PERIOD_LEN <= PRE; start++) {
        bool ok = true;
        for (int k = 0; k < PERIOD_LEN; k++) {
            if (g[start + k] != g[start + PERIOD_LEN + k]) {
                ok = false;
                break;
            }
        }
        if (ok) {
            period_start = start;
            break;
        }
    }

    // Count wins for n = 1..N
    ll ans = 0;
    for (ll n = 1; n <= min(N, (ll)(period_start - 1)); n++) {
        if (g[n] != 0) ans++;
    }

    if (N >= period_start) {
        // Count wins in one period block (length 34)
        int win_in_period = 0;
        for (int k = 0; k < PERIOD_LEN; k++) {
            if (g[period_start + k] != 0) win_in_period++;
        }

        ll remaining = N - period_start + 1;
        ll full_periods = remaining / PERIOD_LEN;
        ans += full_periods * win_in_period;

        ll extra = remaining % PERIOD_LEN;
        for (ll k = 0; k < extra; k++) {
            if (g[period_start + k] != 0) ans++;
        }
    }

    cout << ans << "\n";
    return 0;
}
