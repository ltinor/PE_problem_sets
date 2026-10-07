#include<bits/stdc++.h>
using namespace std;

#define ll long long
const int MOD = 1e9+7;
const int MAXN = 1e7 + 5;

vector<int> primes;
bitset<MAXN> is_composite;

void sieve(int n) {
    for(int i = 2; i <= n; i++) {
        if(!is_composite[i]) primes.push_back(i);
        for(int p : primes) {
            if(1LL * i * p > n) break;
            is_composite[i * p] = 1;
            if(i % p == 0) break;
        }
    }
}

ll solve(int n) {
    ll ans = 1;
    for(int p : primes) {
        if(p > n) break;
        ll cur = p;
        while(cur * p <= n) cur *= p;
        ans = ans * cur % MOD;
    }
    return ans;
}

int main() {

    int T;
    cin >> T;

    vector<int> ns(T);
    int mx = 0;
    for(int i = 0; i < T; i++) {
        cin >> ns[i];
        mx = max(mx, ns[i]);
    }

    sieve(mx);

    for(int n : ns) {
        cout << solve(n) << '\n';
    }
}