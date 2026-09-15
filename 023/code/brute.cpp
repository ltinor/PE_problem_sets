#include<bits/stdc++.h>
using namespace std;
#define ll long long

// brute: for each query compute divisor sum for each number individually
int proper_divisor_sum(int n) {
    if (n <= 1) return 0;
    int sum = 1;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            sum += i;
            int j = n / i;
            if (j != i) sum += j;
        }
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;

        vector<bool> is_abundant(N + 1, false);
        for (int i = 1; i <= N; i++) {
            if (proper_divisor_sum(i) > i) is_abundant[i] = true;
        }

        vector<bool> expressible(N + 1, false);
        for (int i = 1; i <= N; i++) {
            if (!is_abundant[i]) continue;
            for (int j = i; j <= N; j++) {
                if (!is_abundant[j]) continue;
                int s = i + j;
                if (s > N) break;
                expressible[s] = true;
            }
        }

        ll ans = 0;
        for (int i = 1; i <= N; i++) {
            if (!expressible[i]) ans += i;
        }
        cout << ans << "\n";
    }

    return 0;
}
