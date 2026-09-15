#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// Brute: compute Grundy by DP for small n, then verify XOR condition
int v2(ll x) {
    int c = 0;
    while (x % 2 == 0) { x /= 2; c++; }
    return c;
}

int main() {
    string q; getline(cin, q);
    ll n = stoll(q);
    if (n > 200) { cout << "0\n"; return 0; }
    
    // Compute Grundy via definition
    vector<int> G(n+1, 0);
    for (ll x = 2; x <= n; x++) {
        set<int> s;
        for (ll d = 1; d * d <= x; d++) {
            if (x % d == 0) {
                if (d < x) s.insert(G[x - d]);
                ll d2 = x / d;
                if (d2 < x && d2 != d) s.insert(G[x - d2]);
            }
        }
        int mex = 0;
        while (s.count(mex)) mex++;
        G[x] = mex;
    }
    
    // Count winning positions
    ll win = 0;
    for (ll a = 1; a <= n; a++)
        for (ll b = 1; b <= n; b++)
            for (ll c = 1; c <= n; c++)
                if ((G[a] ^ G[b] ^ G[c]) != 0) win++;
    cout << win << "\n";
}
