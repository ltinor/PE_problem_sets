#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

// Brute force: same approach but checks squarefree by trial division up to sqrt(v)
// Works for verification on small N

bool is_squarefree_brute(ll v){
    if(v == 1) return true;
    for(ll d = 2; d*d <= v; d++){
        ll d2 = d*d;
        if(v % d2 == 0) return false;
    }
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    set<ll> distinct;

    for(int n = 0; n <= N; n++){
        ll val = 1;
        distinct.insert(val);
        for(int k = 1; k <= n/2; k++){
            val = val * (n - k + 1) / k;
            distinct.insert(val);
        }
    }

    ll ans = 0;
    for(ll v : distinct){
        if(is_squarefree_brute(v)){
            ans += v;
        }
    }

    cout << ans << "\n";
}
