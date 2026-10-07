#include<bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 5000000;
int chain_len[MAXN + 1]; // memoization

int collatz_len(ll n) {
    if (n <= MAXN && chain_len[n] != 0)
        return chain_len[n];

    int len;
    if (n == 1) {
        len = 1;
    } else if (n % 2 == 0) {
        len = 1 + collatz_len(n / 2);
    } else {
        len = 1 + collatz_len(3 * n + 1);
    }

    if (n <= MAXN)
        chain_len[n] = len;
    return len;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    memset(chain_len, 0, sizeof(chain_len));
    chain_len[1] = 1;

    ll N;
    cin >> N;

    int max_len = 0;
    ll best_start = 1;

    for (ll i = 1; i < N; i++) {
        int cur = collatz_len(i);
        if (cur > max_len) {
            max_len = cur;
            best_start = i;
        }
    }

    cout << best_start << endl;
    return 0;
}
