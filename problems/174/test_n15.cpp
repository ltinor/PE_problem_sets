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
    
    // Count type 15
    int n15 = 0;
    for(int t = 1; t <= M; t++){
        if(c[t] == 15) n15++;
    }
    cout << "N(15) = " << n15 << "\n";
    
    // Sum N(1)..N(10)
    ll total = 0;
    for(int n = 1; n <= 10; n++){
        int cnt = 0;
        for(int t = 1; t <= M; t++){
            if(c[t] == n) cnt++;
        }
        total += cnt;
    }
    cout << "Sum N(1..10) = " << total << "\n";
}
