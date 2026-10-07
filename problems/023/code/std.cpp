#include<bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 28123;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // sieve: compute sum of proper divisors O(N log N)
    vector<int> div_sum(MAXN + 1, 0);
    for (int i = 1; i <= MAXN; i++) {
        for (int j = i * 2; j <= MAXN; j += i) {
            div_sum[j] += i;
        }
    }

    // mark abundant numbers
    vector<bool> is_abundant(MAXN + 1, false);
    for (int i = 1; i <= MAXN; i++) {
        if (div_sum[i] > i) is_abundant[i] = true;
    }

    // mark numbers expressible as sum of two abundant numbers
    vector<bool> expressible(MAXN + 1, false);
    for (int i = 1; i <= MAXN; i++) {
        if (!is_abundant[i]) continue;
        for (int j = i; j <= MAXN; j++) {
            if (!is_abundant[j]) continue;
            int s = i + j;
            if (s > MAXN) break;
            expressible[s] = true;
        }
    }

    // prefix sum of non-expressible numbers
    vector<ll> pref(MAXN + 1, 0);
    for (int i = 1; i <= MAXN; i++) {
        pref[i] = pref[i - 1] + (expressible[i] ? 0 : i);
    }

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        cout << pref[N] << "\n";
    }

    return 0;
}
