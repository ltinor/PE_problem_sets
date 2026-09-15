#include<bits/stdc++.h>
using namespace std;
#define ll long long

// brute: no memoization, compute chain length for each starting number
int collatz_len_brute(ll n) {
    int len = 1;
    while (n != 1) {
        if (n % 2 == 0)
            n /= 2;
        else
            n = 3 * n + 1;
        len++;
    }
    return len;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    int max_len = 0;
    ll best_start = 1;

    for (ll i = 1; i < N; i++) {
        int cur = collatz_len_brute(i);
        if (cur > max_len) {
            max_len = cur;
            best_start = i;
        }
    }

    cout << best_start << endl;
    return 0;
}
