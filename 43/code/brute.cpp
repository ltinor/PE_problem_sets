#include<bits/stdc++.h>
using namespace std;
#define ll long long

int divs[7] = {2, 3, 5, 7, 11, 13, 17};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int dummy;
    cin >> dummy;

    int a[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    ll ans = 0;

    do {
        if (a[0] == 0) continue;

        bool good = true;
        for (int i = 0; i < 7; i++) {
            int v = a[i + 1] * 100 + a[i + 2] * 10 + a[i + 3];
            if (v % divs[i] != 0) { good = false; break; }
        }

        if (good) {
            ll x = 0;
            for (int i = 0; i < 10; i++) x = x * 10 + a[i];
            ans += x;
        }

    } while (next_permutation(a, a + 10));

    cout << ans << "\n";
    return 0;
}
