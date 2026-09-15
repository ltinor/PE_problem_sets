#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Brute force: enumerate all numbers < 10^n for small n

const ll MOD = 14348907;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    // Brute: n <= 6 only
    if (n > 6) { cout << "0\n"; return 0; }
    
    ll limit = 1;
    for (int i = 0; i < n; i++) limit *= 10;
    if (limit > 1000000) limit = 1000000;
    
    ll total = 0;
    for (ll num = 1; num < limit; num++) {
        string s = to_string(num);
        int k = s.size();
        int half = (k + 1) / 2;
        int s1 = 0, s2 = 0;
        for (int i = 0; i < half; i++) s1 += s[i] - '0';
        for (int i = k - half; i < k; i++) s2 += s[i] - '0';
        if (s1 == s2) {
            total = (total + num % MOD) % MOD;
        }
    }
    
    cout << total << "\n";
}
