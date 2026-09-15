#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 1000000007LL;

ll brute(ll N) {
    ll s = 0;
    for (ll i = 1; i <= N; i++) {
        int pc = __builtin_popcountll(i);
        ll fi = (i % MOD) * pc % MOD;
        s = (s + fi * fi) % MOD;
    }
    return s;
}

// Include the solve function from std.cpp
// Actually, let me just compile with std.cpp
int main() {
    for (ll N : {10LL, 100LL, 1000LL, 10000LL, 100000LL, 1000000LL}) {
        ll b = brute(N);
        cout << "N=" << N << " brute_mod=" << b << "\n";
    }
    cout << "\nNow compute from the DP: compile with std.cpp\n";
    return 0;
}
