#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool can_tile(ll a, ll b) {
    if (a > b) swap(a, b);
    if (a == 1 || a == 2 || a == 4) return true;
    if (a % 2 == 1) return b >= 2 * a;
    if (a % 4 == 2) return b >= 3 * a;
    return b >= 4 * a;
}

int main() {
    for (ll s : {70, 1080, 1320}) {
        ll t = 0;
        cout << "s=" << s << " tatami-free: ";
        for (ll a = 1; a * a <= s; a++) {
            if (s % a != 0) continue;
            ll b = s / a;
            if (!can_tile(a, b)) {
                t++;
                cout << "(" << a << "," << b << ") ";
            }
        }
        cout << " total=" << t << endl;
    }
    // Test specific rooms
    cout << "\nSpecific checks:" << endl;
    cout << "18x60 tileable? " << can_tile(18,60) << endl;
    cout << "30x36 tileable? " << can_tile(30,36) << endl;
}
