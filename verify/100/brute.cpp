#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll T;
    cin >> T;

    ll b = 3, t = 4;
    while (t <= T) {
        ll nb = 3 * b + 2 * t - 2;
        ll nt = 4 * b + 3 * t - 3;
        b = nb;
        t = nt;
    }

    cout << b << "\n";
    return 0;
}
