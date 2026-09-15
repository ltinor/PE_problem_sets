#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    int M = 100;
    map<ll,int> cnt;
    for(int a = 3; a <= M; a++){
        for(int b = a - 2; b >= 1; b -= 2){
            ll tiles = (ll)a*a - (ll)b*b;
            if(tiles > M) break;
            cnt[tiles]++;
        }
    }
    cout << "M=100 distinct laminae: " << cnt.size() << " t values, ";
    ll total_pairs = 0;
    for(auto& [t, c] : cnt) total_pairs += c;
    cout << total_pairs << " pairs\n";
    
    vector<int> N(20, 0);
    for(auto& [t, c] : cnt){
        if(c >= 1 && c <= 10) N[c]++;
    }
    int sum_n_1_10 = 0;
    for(int n = 1; n <= 10; n++) sum_n_1_10 += N[n];
    cout << "Sum N(1..10) for M=100: " << sum_n_1_10 << "\n";
    
    // Also check N(15) for M=1000000
    M = 1000000;
    vector<int> c2(M + 1, 0);
    for(int k = 1; ; k++){
        ll min_tiles = 4LL * k * (1 + k);
        if(min_tiles > M) break;
        ll max_b = M / (4LL * k) - k;
        for(int b = 1; b <= max_b; b++){
            ll t = 4LL * k * (b + k);
            if(t <= M) c2[t]++;
        }
    }
    int n15 = 0;
    for(int t = 1; t <= M; t++) if(c2[t] == 15) n15++;
    cout << "N(15) = " << n15 << " (should be 832)\n";
    return 0;
}
