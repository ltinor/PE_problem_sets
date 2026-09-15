#include<bits/stdc++.h>
using namespace std;
#define ll long long

// brute: enumerate all numbers up to 10^D for small D, check rotation property

const ll MOD = 100000;

// Compute 10^k
ll pow10(int k){
    ll r = 1;
    for(int i = 0; i < k; i++) r *= 10;
    return r;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int D;
    cin >> D;
    
    ll ans = 0;
    
    // For brute, we can only handle small D (like D <= 6)
    if(D <= 6){
        ll limit = 1;
        for(int i = 0; i < D; i++) limit *= 10;
        
        for(ll n = 11; n < limit; n++){
            // Count digits
            ll tmp = n;
            int k = 0;
            while(tmp){ k++; tmp /= 10; }
            
            // Right rotate
            ll last_digit = n % 10;
            ll rest = n / 10;
            ll rotated = last_digit * pow10(k-1) + rest;
            
            if(rotated % n == 0 && rotated / n >= 2 && rotated / n <= 9){
                ans = (ans + n) % MOD;
            }
        }
    } else {
        // For larger D, use same algorithm as std but simplified
        for(int k = 2; k <= D && k <= 18; k++){
            ll p10km1 = 1;
            for(int i = 0; i < k-1; i++) p10km1 *= 10;
            
            ll p10k = p10km1 * 10;
            
            for(int b = 1; b <= 9; b++){
                for(int m = 2; m <= 9; m++){
                    ll denom = 10*m - 1;
                    
                    // Check: b * (10^{k-1} - m) divisible by denom
                    if((b * (p10km1 - m)) % denom != 0) continue;
                    
                    // Compute a = b * (10^{k-1} - m) / denom
                    ll a = b * (p10km1 - m) / denom;
                    
                    // n = 10a + b must have exactly k digits
                    if(a < p10km1 / 10) continue; // a too small
                    if(a >= p10km1) continue; // a too large
                    
                    ll n = 10*a + b;
                    ans = (ans + n) % MOD;
                }
            }
        }
    }
    
    cout << ans << "\n";
}
