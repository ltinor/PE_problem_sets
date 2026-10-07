#include<bits/stdc++.h>
using namespace std;
#define ll long long

// brute: compute f(N) using DP for small N, verify recurrence

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll N;
    cin >> N;
    
    // Use DP for small N (N <= 10^6)
    vector<ll> f(N + 1, 0);
    f[0] = 1;
    
    for(ll i = 1; i <= N; i++){
        if(i % 2 == 0){
            f[i] = f[i/2] + f[i/2 - 1];
        } else {
            f[i] = f[i/2];
        }
    }
    
    cout << f[N] << "\n";
}
