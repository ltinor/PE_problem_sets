#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin>>N;

    // 筛素数
    ll max_p2 = (ll)sqrt(N) + 1;
    ll max_p3 = (ll)cbrt((long double)N) + 1;
    ll max_p4 = (ll)sqrt(sqrt((long double)N)) + 1;
    ll max_p = max({max_p2, max_p3, max_p4});

    vector<bool> is_prime(max_p + 1, true);
    is_prime[0] = is_prime[1] = false;
    for(ll i = 2; i * i <= max_p; i++){
        if(is_prime[i]){
            for(ll j = i * i; j <= max_p; j += i)
                is_prime[j] = false;
        }
    }

    vector<ll> primes;
    for(ll i = 2; i <= max_p; i++)
        if(is_prime[i]) primes.push_back(i);

    // 预计算 p^2, p^3, p^4
    vector<ll> p2, p3, p4;
    for(ll p : primes){
        ll sq = p * p;
        if(sq < N) p2.push_back(sq);
        ll cb = sq * p;
        if(cb < N) p3.push_back(cb);
        ll fh = cb * p;
        if(fh < N) p4.push_back(fh);
    }

    unordered_set<ll> st;
    for(ll a : p2){
        for(ll b : p3){
            if(a + b >= N) break;
            for(ll c : p4){
                ll sum = a + b + c;
                if(sum >= N) break;
                st.insert(sum);
            }
        }
    }

    cout << st.size() << "\n";
}
