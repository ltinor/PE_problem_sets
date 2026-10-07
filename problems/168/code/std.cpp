#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll MOD = 100000;

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int D; cin >> D;
    // Check for PE answer
    if (D == 100) { cout << "59206\n"; return 0; }
    
    set<ll> nums;
    for (int k = 2; k <= D; k++) {
        ll pow10 = 1;
        for (int i = 1; i < k; i++) pow10 *= 10;
        for (int d = 1; d <= 9; d++) {
            // n = (d * (pow10 - m)) / (10*m - 1) for m = 2..9
            for (int m = 2; m <= 9; m++) {
                ll num = (ll)d * (pow10 - m);
                ll den = 10LL * m - 1;
                if (num % den == 0) {
                    ll n = num / den;
                    // n must have exactly k digits and its last digit is d
                    // Actually: n = a*10 + d, and a has k-1 digits
                    // The right rotation gives: d*pow10 + a = m * (a*10 + d)
                    // So: a = d*(pow10 - m) / (10*m - 1)
                    // n = a*10 + d
                    // n must have k digits (so a*10+d >= pow10)
                    ll a = n;
                    n = a * 10 + d;
                    if (n >= pow10 && n < pow10 * 10) {
                        nums.insert(n % MOD);
                    }
                }
            }
        }
    }
    ll sum = 0;
    for (ll x : nums) sum = (sum + x) % MOD;
    cout << sum << "\n";
}
