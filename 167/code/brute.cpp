#include<bits/stdc++.h>
using namespace std;
#define ll long long

// brute: generate Ulam sequence directly for small K to verify the pattern

vector<ll> generate_ulam(ll a, ll b, ll K){
    if(K == 1) return {a};
    if(K == 2) return {a, b};
    
    vector<ll> seq = {a, b};
    unordered_map<ll, int> cnt;
    cnt[a + b] = 1;
    ll last = b;
    
    while((ll)seq.size() < K){
        ll x = last + 1;
        while(true){
            // For brute, scan numbers sequentially
            auto it = cnt.find(x);
            if(it != cnt.end() && it->second == 1) break;
            x++;
        }
        
        seq.push_back(x);
        for(ll prev : seq){
            if(prev == x) break;
            cnt[prev + x]++;
        }
        last = x;
    }
    
    return seq;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll K;
    cin >> K;
    
    ll ans = 0;
    for(int n = 2; n <= 10; n++){
        auto seq = generate_ulam(2, 2*n+1, K);
        ans += seq.back();
    }
    
    cout << ans << "\n";
}
