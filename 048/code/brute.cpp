#include<bits/stdc++.h>
using namespace std;
#define ll long long

const ll MOD = 10000000000LL;

// Safe multiplication
ll mul_mod(ll a, ll b){
    return (ll)(((__int128)a * b) % MOD);
}

// Simple modular exponentiation (independent implementation)
ll mod_pow(ll base, ll exp){
    ll result = 1;
    base %= MOD;
    for(ll i = 0; i < exp; i++){
        result = mul_mod(result, base);
    }
    return result;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll N;
    while(cin >> N){
        ll sum = 0;
        for(ll i = 1; i <= N; i++){
            sum = (sum + mod_pow(i, i)) % MOD;
        }
        cout << setw(10) << setfill('0') << sum << "\n";
    }
    
    return 0;
}
