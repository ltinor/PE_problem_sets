#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const string DIGITS = "123432";

// Brute: verify v_n by simulation for very small n
int main() {
    string query;
    getline(cin, query);
    ll N = stoll(query);
    
    if (N > 1000) { cout << "0\n"; return 0; }
    
    ll pos = 0;
    ll ans = 0;
    const ll MOD = 123454321LL;
    
    for (ll n = 1; n <= N; n++) {
        ll sum = 0;
        ll val = 0;
        while (sum < n) {
            int d = DIGITS[pos % 6] - '0';
            sum += d;
            val = val * 10 + d;
            pos++;
        }
        ans = (ans + val) % MOD;
    }
    cout << ans << "\n";
}
