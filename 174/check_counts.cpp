#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    int M = 1000000;
    vector<int> c(M + 1, 0);
    for(int k = 1; ; k++){
        ll min_tiles = 4LL * k * (1 + k);
        if(min_tiles > M) break;
        ll max_b = M / (4LL * k) - k;
        for(int b = 1; b <= max_b; b++){
            ll t = 4LL * k * (b + k);
            if(t <= M) c[t]++;
        }
    }
    
    vector<int> max_n_for_t(M+1, 0);
    for(int n = 1; n <= 100; n++){
        int cnt = 0;
        for(int t = 1; t <= M; t++){
            if(c[t] == n) cnt++;
        }
        if(cnt > 0) cout << "N(" << n << ") = " << cnt << "\n";
    }
    
    // Total distinct (k,b) pairs
    ll pairs = 0;
    for(int t = 1; t <= M; t++) pairs += c[t];
    cout << "Total (k,b) pairs = " << pairs << "\n";
}
