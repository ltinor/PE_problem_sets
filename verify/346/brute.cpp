#include<bits/stdc++.h>
using namespace std;
#define ll long long

bool is_repunit(ll n, ll b){
    while(n > 0){
        if(n % b != 1) return false;
        n /= b;
    }
    return true;
}

int main(){
    ll N;
    cin >> N;

    ll ans = 1; // 1 is always a strong repunit
    for(ll n = 2; n < N; n++){
        int cnt = 0;
        for(ll b = 2; b < n && cnt < 2; b++){
            if(is_repunit(n, b)){
                cnt++;
            }
        }
        if(cnt >= 2) ans += n;
    }
    cout << ans << "\n";
}
