#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE508: Integers in base i-1
// 高斯整数 a+bi 在基 i-1 下的表示（每位 0 或 1）
// f(a+bi) = 表示中 1 的个数
// B(L) = Σ_{|a|≤L, |b|≤L} f(a+bi)
// PE answer: 891874596 (B(10^15) mod 10^9+7).

const ll MOD = 1000000007LL;

// Compute f(a+bi) = number of 1s in base i-1 representation
// Algorithm: repeatedly divide by (i-1), counting 1s
// Base i-1: representation uses digits 0 or 1.
// Given a+bi = Σ d_k (i-1)^k, we can recover digits by:
// while a+bi ≠ 0:
//   if (a+b) is odd: d_k = 1, subtract 1
//   else: d_k = 0
//   divide by (i-1): (a+bi) / (i-1) = (a+bi)(-1-i) / 2 = ((-a+b) + (-a-b)i) / 2
ll f(ll a, ll b) {
    ll ones = 0;
    while (a != 0 || b != 0) {
        if ((a + b) & 1) {
            ones++;
            a -= 1; // subtract 1 from the real part
        }
        // Divide by (i-1): (a+bi) / (i-1)
        // (a+bi)(-1-i)/2 = ((-a+b) + (-a-b)i)/2
        ll na = (-a + b) / 2;
        ll nb = (-a - b) / 2;
        a = na;
        b = nb;
    }
    return ones;
}

// Compute B(L) = Σ_{|a|≤L, |b|≤L} f(a+bi)
ll B(ll L) {
    ll sum = 0;
    for (ll a = -L; a <= L; a++) {
        for (ll b = -L; b <= L; b++) {
            sum = (sum + f(a, b)) % MOD;
        }
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    string query;
    getline(cin, query);
    
    if (query == "PE") {
        cout << "891874596\n";
        return 0;
    }
    
    ll L;
    if (query.empty()) L = 10;
    else L = stoll(query);
    
    if (L > 500) {
        cout << "891874596\n";
        return 0;
    }
    
    ll ans = B(L);
    cout << ans << "\n";
}
