#include<bits/stdc++.h>
using namespace std;
#define ll long long

// brute: enumerate all D-digit numbers for small D (D <= 6)

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int D;
    cin >> D;

    // Small D brute force
    ll start = 1;
    for(int i = 1; i < D; i++) start *= 10;
    ll end = start * 10;

    ll total = 0;
    for(ll n = start; n < end; n++){
        int cnt[10] = {0};
        ll tmp = n;
        bool ok = true;
        while(tmp > 0){
            int d = tmp % 10;
            cnt[d]++;
            if(cnt[d] > 3){ ok = false; break; }
            tmp /= 10;
        }
        if(ok) total++;
    }

    cout << total << "\n";
}
