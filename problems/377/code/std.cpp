#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE377: f(n) = sum of numbers with digit sum n and no zero digits.
// Find sum_{i=1..K} f(13^i) mod 10^9.
//
// DP recurrences (digits 1..9 only):
// cnt[n] = Σ_{d=1..9} cnt[n-d], cnt[0]=1
// sum[n] = Σ_{d=1..9} (10·sum[n-d] + d·cnt[n-d]), sum[0]=0
//
// 18×18 matrix: [cnt[n-1]..cnt[n-9] | sum[n-1]..sum[n-9]] → next
// PE answer: 732385277

const ll MOD = 1000000000;

struct Mat { ll a[18][18]; Mat() { memset(a, 0, sizeof(a)); } };

Mat mul(const Mat& A, const Mat& B) {
    Mat C;
    for (int i = 0; i < 18; i++)
        for (int k = 0; k < 18; k++)
            if (A.a[i][k])
                for (int j = 0; j < 18; j++)
                    C.a[i][j] = (C.a[i][j] + A.a[i][k] * B.a[k][j]) % MOD;
    return C;
}

Mat matpow(Mat M, ll e) {
    Mat R; for (int i = 0; i < 18; i++) R.a[i][i] = 1;
    while (e) { if (e & 1) R = mul(R, M); M = mul(M, M); e >>= 1; }
    return R;
}

ll f(ll n) {
    if (n <= 0) return 0;
    
    // Direct DP for small n
    if (n <= 100) {
        vector<ll> cnt(n+1, 0), sm(n+1, 0);
        cnt[0] = 1;
        for (int s = 1; s <= n; s++)
            for (int d = 1; d <= 9 && d <= s; d++) {
                cnt[s] = (cnt[s] + cnt[s-d]) % MOD;
                sm[s] = (sm[s] + 10*sm[s-d] + d*cnt[s-d]) % MOD;
            }
        return sm[n];
    }
    
    // Build transition matrix T
    Mat T;
    // cnt row: cnt[n] = cnt[n-1] + ... + cnt[n-9]
    for (int d = 0; d < 9; d++) T.a[0][d] = 1;
    for (int i = 1; i < 9; i++) T.a[i][i-1] = 1;
    // sum row: sum[n] = Σ(10·sum[n-d] + d·cnt[n-d])
    for (int d = 0; d < 9; d++) {
        T.a[9][d] = d + 1;        // coefficient of cnt[n-(d+1)]
        T.a[9][9 + d] = 10;        // coefficient of sum[n-(d+1)]
    }
    for (int i = 10; i < 18; i++) T.a[i][i-1] = 1;
    
    // Compute initial state at n=9
    vector<ll> cnt(10, 0), sm(10, 0);
    cnt[0] = 1;
    for (int s = 1; s <= 9; s++)
        for (int d = 1; d <= s; d++) {
            cnt[s] = (cnt[s] + cnt[s-d]) % MOD;
            sm[s] = (sm[s] + 10*sm[s-d] + d*cnt[s-d]) % MOD;
        }
    
    // State at n=9: [cnt[9], cnt[8], ..., cnt[1], sum[9], sum[8], ..., sum[1]]
    ll init[18];
    for (int i = 0; i < 9; i++) init[i] = cnt[9 - i];
    for (int i = 0; i < 9; i++) init[9 + i] = sm[9 - i];
    
    Mat Tp = matpow(T, n - 9);
    
    // Result state: state[n] = Tp × state[9]
    // sum[n] is the 10th element (index 9)
    ll res = 0;
    for (int i = 0; i < 18; i++)
        res = (res + Tp.a[9][i] * init[i]) % MOD;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int K;
    cin >> K;
    
    ll total = 0, p13 = 1;
    for (int i = 1; i <= K; i++) {
        p13 *= 13;
        total = (total + f(p13)) % MOD;
    }
    cout << total << "\n";
    return 0;
}
