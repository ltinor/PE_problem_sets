#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE356: Largest roots of cubic polynomial x^3 - 2^n * x^2 + n
// Recurrence: S_m = 2^n * S_{m-1} - n * S_{m-3}
// S_0=3, S_1=2^n, S_2=2^{2n}
// floor(a_n^K) = S_K - 1 (for all n=1..30)
// PE answer: 28010159 (last 8 digits)

struct Mat {
    ll a[3][3];
    Mat() { memset(a, 0, sizeof(a)); }
};

Mat mul(const Mat& A, const Mat& B, ll mod) {
    Mat C;
    for (int i = 0; i < 3; i++)
        for (int k = 0; k < 3; k++)
            if (A.a[i][k])
                for (int j = 0; j < 3; j++)
                    C.a[i][j] = (C.a[i][j] + A.a[i][k] * B.a[k][j]) % mod;
    return C;
}

Mat matpow(Mat M, ll e, ll mod) {
    Mat R;
    for (int i = 0; i < 3; i++) R.a[i][i] = 1;
    while (e) {
        if (e & 1) R = mul(R, M, mod);
        M = mul(M, M, mod);
        e >>= 1;
    }
    return R;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N, K, MOD;
    cin >> N >> K >> MOD;

    ll total = 0;
    for (ll n = 1; n <= N; n++) {
        // Compute 2^n mod MOD
        ll tn = 1;
        for (ll i = 0; i < n; i++) tn = (tn * 2) % MOD;
        
        Mat M;
        M.a[0][0] = tn;
        M.a[0][2] = (MOD - n % MOD) % MOD;
        M.a[1][0] = 1;
        M.a[2][1] = 1;

        ll S2 = tn * tn % MOD;
        ll S1 = tn;
        ll S0 = 3 % MOD;

        ll Sk;
        if (K == 0) Sk = S0;
        else if (K == 1) Sk = S1;
        else if (K == 2) Sk = S2;
        else {
            Mat Mp = matpow(M, K - 2, MOD);
            Sk = (Mp.a[0][0] * S2 + Mp.a[0][1] * S1 + Mp.a[0][2] * S0) % MOD;
        }

        // floor(a_n^K) = S_K - 1
        ll floor_val = (Sk - 1 + MOD) % MOD;
        total = (total + floor_val) % MOD;
    }

    cout << total << "\n";
    return 0;
}
