#include<bits/stdc++.h>
using namespace std;

#define ll long long

// Brute force for small K (K <= 12, N = 2^K <= 4096)
// Check each number for squarefree property

bool is_squarefree(ll n) {
    if (n % 4 == 0) return false;
    for (ll i = 3; i * i <= n; i += 2) {
        if (n % (i * i) == 0) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    cin >> K;

    ll N = 1LL << K;
    ll ans = 0;

    for (ll i = 1; i < N; i++) {
        if (is_squarefree(i)) ans++;
    }

    cout << ans << "\n";
    return 0;
}
