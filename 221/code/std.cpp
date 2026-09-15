#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define i128 __int128

// Alexandrian Integers
// A > 0, 存在整数 p,q,r: A = pqr, 且 pq+pr+qr = 1
// 即 (p+q)(p+r) = p^2+1。设 p=k>0, 则 (k+q)(k+r)=k^2+1。
// d = k+q, n/d = k+r（d 为 k^2+1 的因子），q,r 均为负 → A = k(d+k)(n/d+k) > 0。
// 前 6 个: 6, 42, 120, 156, 420, 630。
// 答案: 第 150000 个 = 1884161251122450。

const int MAX_K = 800000;

vector<int> primes;
vector<char> is_composite;

void sieve(int n) {
    is_composite.assign(n + 1, 0);
    for(int i = 2; i <= n; i++) {
        if(!is_composite[i]) {
            primes.push_back(i);
            if((ll)i * i <= n)
                for(ll j = (ll)i * i; j <= n; j += i) is_composite[j] = 1;
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll K;
    cin >> K;

    sieve(MAX_K);

    vector<ll> alex;
    alex.reserve(2000000);

    for(ll k = 1; k <= MAX_K; k++) {
        ll n = k * k + 1;
        // factor n
        vector<pair<ll,int>> fac;
        ll tmp = n;
        for(int p : primes) {
            if((ll)p * p > tmp) break;
            if(tmp % p == 0) {
                int c = 0;
                while(tmp % p == 0) { tmp /= p; c++; }
                fac.push_back({p, c});
            }
        }
        if(tmp > 1) fac.push_back({tmp, 1});

        // divisors
        vector<ll> divs = {1};
        for(auto& [p, e] : fac) {
            int sz = divs.size();
            ll pe = 1;
            for(int i = 1; i <= e; i++) {
                pe *= p;
                for(int j = 0; j < sz; j++) divs.push_back(divs[j] * pe);
            }
        }

        for(ll d : divs) {
            ll q = -d - k;
            ll r = -n / d - k;
            if(q == 0 || r == 0) continue;
            i128 A = (i128)k * (-q) * (-r);
            if(A > 0 && A < (i128)9000000000000000000LL) {
                alex.push_back((ll)A);
            }
        }
    }

    sort(alex.begin(), alex.end());
    alex.erase(unique(alex.begin(), alex.end()), alex.end());

    if(K <= (ll)alex.size()) {
        cout << alex[K - 1] << "\n";
    }
    return 0;
}
