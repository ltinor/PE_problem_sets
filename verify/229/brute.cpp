#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Brute force verification (same as std but simpler for small N)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    vector<unsigned char> mask(N + 1, 0);
    int ds[] = {1, 2, 3, 7};

    for (int idx = 0; idx < 4; idx++) {
        int d = ds[idx];
        for (ll a = 1; a * a + d <= N; a++) {
            ll a2 = a * a;
            for (ll b = 1; ; b++) {
                ll n = a2 + d * b * b;
                if (n > N) break;
                mask[n] |= (1 << idx);
            }
        }
    }

    ll cnt = 0;
    for (ll n = 1; n <= N; n++) {
        if (mask[n] == 0b1111) cnt++;
    }

    cout << cnt << "\n";
    return 0;
}
