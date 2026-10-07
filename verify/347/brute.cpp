#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    ll N;
    cin >> N;

    // Collect all primes up to N
    vector<bool> is_prime(N+1, true);
    vector<ll> primes;
    is_prime[0] = is_prime[1] = false;
    for(ll i = 2; i <= N; i++){
        if(is_prime[i]){
            primes.push_back(i);
            for(ll j = i*i; j <= N; j += i) is_prime[j] = false;
        }
    }

    unordered_set<ll> used;
    ll ans = 0;

    for(size_t i = 0; i < primes.size(); i++){
        ll p = primes[i];
        for(size_t j = i+1; j < primes.size(); j++){
            ll q = primes[j];
            if(p * q > N) break;
            ll best = 0;
            for(ll pa = p; pa <= N; pa *= p){
                for(ll qb = q; pa * qb <= N; qb *= q){
                    best = max(best, pa * qb);
                }
            }
            if(best > 0 && !used.count(best)){
                used.insert(best);
                ans += best;
            }
        }
    }
    cout << ans << "\n";
}
