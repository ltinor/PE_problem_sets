#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int K;
        cin >> K;

        ll pow10[10];
        for (int d = 0; d <= 9; d++) {
            ll p = 1;
            for (int k = 0; k < K; k++) p *= d;
            pow10[d] = p;
        }

        ll upper = 7 * pow10[9] + 1;

        ll total = 0;
        for (ll n = 2; n <= upper; n++) {
            ll sum = 0;
            ll tmp = n;
            while (tmp > 0) {
                sum += pow10[tmp % 10];
                tmp /= 10;
            }
            if (sum == n) {
                total += n;
            }
        }
        cout << total << "\n";
    }
    return 0;
}
