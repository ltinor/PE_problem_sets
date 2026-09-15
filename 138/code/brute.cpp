#include<bits/stdc++.h>
using namespace std;

#define ll long long

// Brute force: same Pell recurrence, same as std
// x^2 - 5y^2 = -1, generate solutions and count L=y

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    cin >> K;

    ll x = 2, y = 1;
    ll sum = 0;
    int cnt = 0;

    while (cnt < K) {
        ll nx = 9 * x + 20 * y;
        ll ny = 4 * x + 9 * y;
        x = nx;
        y = ny;

        if (x % 5 == 2 || x % 5 == 3) {
            sum += y;
            cnt++;
        }
    }

    cout << sum << "\n";
    return 0;
}
