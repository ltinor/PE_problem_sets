#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

// PE 204 — Generalised Hamming Numbers
// Count numbers ≤ m whose prime factors are all ≤ n

vector<int> primes;

void gen_primes(int n){
    vector<bool> is_prime(n+1, true);
    for(int i = 2; i <= n; i++){
        if(is_prime[i]){
            primes.push_back(i);
            for(int j = i*i; j <= n; j += i) is_prime[j] = false;
        }
    }
}

ll dfs(int idx, ll cur, ll m){
    if(idx >= (int)primes.size()) return 1;
    ll ans = 0;
    // don't take this prime
    ans += dfs(idx+1, cur, m);
    // take this prime
    ll p = primes[idx];
    while(cur <= m / p){
        cur *= p;
        ans += dfs(idx+1, cur, m);
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    ll m;
    cin >> n >> m;

    gen_primes(n);
    ll ans = dfs(0, 1, m);
    cout << ans << "\n";
}
