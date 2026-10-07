#include<bits/stdc++.h>
using namespace std;

// PE 169: f(N) = number of ways to express N as sum of powers of 2, each at most twice
// Recurrence:
//   f(0) = 1
//   If N is even: f(N) = f(N/2) + f(N/2 - 1)
//   If N is odd:  f(N) = f(N/2)
//
// N up to 10^25 fits in __int128

using u128 = unsigned __int128;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string s;
    cin >> s;
    
    // Parse to u128
    u128 N = 0;
    for(char c : s) N = N * 10 + (c - '0');
    
    // Use map for memoization
    map<u128, u128> dp;
    
    function<u128(u128)> f = [&](u128 n) -> u128 {
        if(n == 0) return 1;
        auto it = dp.find(n);
        if(it != dp.end()) return it->second;
        
        u128 half = n / 2;
        u128 res = f(half);
        if(n % 2 == 0 && half > 0){
            res += f(half - 1);
        }
        dp[n] = res;
        return res;
    };
    
    u128 ans = f(N);
    
    // Output as string
    string out;
    if(ans == 0) out = "0";
    while(ans > 0){
        out = char('0' + ans % 10) + out;
        ans /= 10;
    }
    cout << out << "\n";
}
