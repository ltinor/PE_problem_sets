#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

// Brute force for small b: enumerate all possible a and check conditions
// Only works for small n (derived from b)

ll mygcd(ll a, ll b){
    while(b){ll t=b; b=a%b; a=t;}
    return a;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll b;
    cin >> b;

    if((b + 3) % 2 != 0){
        cout << "0\n";
        return 0;
    }

    ll n = (b + 3) / 2;
    if(n <= 1){
        cout << "0\n";
        return 0;
    }

    ll cnt = 0;
    for(ll a = 1; a < n; a++){
        if(mygcd(a, n) == 1 && a % 3 != 0){
            cnt++;
        }
    }

    ll ans = cnt / 2;
    cout << ans << "\n";
}
