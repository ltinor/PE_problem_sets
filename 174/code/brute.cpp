#include<bits/stdc++.h>
using namespace std;
#define ll long long

// brute: same as std but for small M

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, K;
    cin >> M >> K;

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

    vector<int> N_counts(K + 1, 0);
    for(int t = 1; t <= M; t++){
        if(c[t] >= 1 && c[t] <= K){
            N_counts[c[t]]++;
        }
    }

    ll total = 0;
    for(int n = 1; n <= K; n++){
        total += N_counts[n];
    }

    cout << total << "\n";
}
