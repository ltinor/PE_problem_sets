#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    int M = 1000000;
    vector<int> c(M + 1, 0);
    
    // Direct (a,b) enumeration - same parity
    for(int a = 3; ; a++){
        ll a2 = (ll)a * a;
        if(a2 - (ll)(a-2)*(a-2) > M) break;
        for(int b = a - 2; b >= 1; b -= 2){
            ll tiles = a2 - (ll)b * b;
            if(tiles > M) break;
            c[tiles]++;
        }
    }
    
    int n15 = 0;
    for(int t = 1; t <= M; t++) if(c[t] == 15) n15++;
    cout << "N(15) via (a,b) enum = " << n15 << "\n";
    
    ll sum = 0;
    for(int n = 1; n <= 10; n++){
        int cnt = 0;
        for(int t = 1; t <= M; t++) if(c[t] == n) cnt++;
        sum += cnt;
    }
    cout << "Sum N(1..10) via (a,b) enum = " << sum << "\n";
    return 0;
}
