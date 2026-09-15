#include<bits/stdc++.h>
using namespace std;
#define ll long long

const ll MOD = 10000000000LL; // 10^10

// Safe multiplication: (a * b) % MOD using __int128 to avoid overflow
ll mul_mod(ll a, ll b){
    return (ll)(((__int128)a * b) % MOD);
}

// Fast exponentiation modulo MOD
ll fast_pow(ll base, ll exp){
    ll result = 1;
    base %= MOD;
    while(exp > 0){
        if(exp & 1) result = mul_mod(result, base);
        base = mul_mod(base, base);
        exp >>= 1;
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
            sum = (sum + fast_pow(i, i)) % MOD;
        }
        // Output last 10 digits with leading zeros
        cout << setw(10) << setfill('0') << sum << "\n";
    }
    
    return 0;
}
