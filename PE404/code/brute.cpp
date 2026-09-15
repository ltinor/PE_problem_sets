#include<bits/stdc++.h>
using namespace std;
using ll = long long;
// PE404 brute: enumerate a, search for b,c satisfying 1/b²+1/c²=5/(4a²)
// From equation: 4a²(b²+c²) = 5b²c² → c² = 4a²b²/(5b²-4a²)

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll N; cin >> N;
    ll cnt = 0;
    for (ll a = 1; a <= N; a++) {
        for (ll b = a + 1; b < 2 * a; b++) {
            ll num = 4 * a * a * b * b;
            ll den = 5 * b * b - 4 * a * a;
            if (den <= 0) continue;
            if (num % den != 0) continue;
            ll c2 = num / den;
            ll c = (ll)sqrt(c2);
            if (c * c == c2 && c > b && c <= 2 * a) {
                cnt++;
            }
        }
    }
    cout << cnt << "\n";
}
