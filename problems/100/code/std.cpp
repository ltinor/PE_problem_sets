#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll T;
    cin >> T;

    // Initial solution: b=3, t=4 (3 blue out of 4 total)
    // 2*3*2/(4*3) = 12/12 = 1/2
    ll b = 3, t = 4;

    // Generate sequence until t > T
    while (t <= T) {
        ll nb = 3 * b + 2 * t - 2;
        ll nt = 4 * b + 3 * t - 3;
        b = nb;
        t = nt;
    }

    cout << b << "\n";
    return 0;
}
