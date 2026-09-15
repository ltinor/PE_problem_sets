#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// Brute force for PE498: compute product directly

int main() {
    string query;
    getline(cin, query);
    stringstream ss(query);
    ll n, d, mod;
    ss >> n >> d >> mod;
    if (mod == 0) mod = 1000000007LL;
    
    if (n >= d) {
        cout << "0\n";
        return 0;
    }
    
    i128 ans = 1;
    for (ll i = 1; i <= n; i++) {
        ans = ans * (d - i) % mod;
    }
    cout << (ll)ans << "\n";
}
