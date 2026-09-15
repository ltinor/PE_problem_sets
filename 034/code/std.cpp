#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Precompute factorials 0!..9!
    int fact[10];
    fact[0] = 1;
    for (int i = 1; i <= 9; i++) {
        fact[i] = fact[i - 1] * i;
    }

    // Precompute digit-factorial-sum for all numbers up to 7*9! = 2540160
    // But N ≤ 10^6, so max is 10^6
    const int MAXN = 1000000;
    // Precompute sums once
    static ll pre[MAXN + 1];
    static bool done = false;
    if (!done) {
        done = true;
        pre[0] = 0;
        for (int i = 1; i <= MAXN; i++) {
            ll sum = 0;
            int tmp = i;
            while (tmp > 0) {
                sum += fact[tmp % 10];
                tmp /= 10;
            }
            if (sum == i && i != 1 && i != 2) {
                pre[i] = pre[i - 1] + i;
            } else {
                pre[i] = pre[i - 1];
            }
        }
    }

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        cout << pre[min(N, MAXN)] << "\n";
    }
    return 0;
}
