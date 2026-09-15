#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int d;
    cin >> d;

    ll L = 1, R;
    for (int i = 1; i < d; i++) L *= 10;
    R = L * 10 - 1;

    ll x0;
    if (d % 2 == 1) {
        x0 = 2;
        for (int i = 0; i < (d - 1) / 2; i++) x0 *= 10;
    } else {
        x0 = 7;
        for (int i = 0; i < (d - 2) / 2; i++) x0 *= 10;
    }

    ll total_iter = 0;
    for (ll n = L; n <= R; n++) {
        ll x = x0;
        int iter = 0;
        while (true) {
            iter++;
            ll nx = (x + (n + x - 1) / x) / 2;
            if (nx == x) break;
            x = nx;
        }
        total_iter += iter;
    }

    ll count = R - L + 1;
    double avg = (double)total_iter / count;
    cout << fixed << setprecision(10) << avg << "\n";
    return 0;
}
