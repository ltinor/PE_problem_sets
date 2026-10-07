#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll M;
    cin >> M;

    ll ans = 0;
    // Pell equation: x^2 - 3y^2 = 4
    // Recurrence: (x_{n+1}, y_{n+1}) = (2*x_n + 3*y_n, x_n + 2*y_n)
    // Start from (4, 2), then generate (14, 8), (52, 30), (194, 112), ...
    ll x = 4, y = 2;

    while (true) {
        ll nx = 2*x + 3*y;
        ll ny = x + 2*y;
        x = nx;
        y = ny;

        ll P = 0;
        if (x % 3 == 2) {
            // Case 1: x = 3a - 1, P = x + 2
            P = x + 2;
        } else if (x % 3 == 1) {
            // Case 2: x = 3a + 1, P = x - 2
            P = x - 2;
        }

        if (P > M) break;
        ans += P;
    }

    cout << ans << "\n";
    return 0;
}
