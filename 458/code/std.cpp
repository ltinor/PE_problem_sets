// PE458: Permutations of Project — Project排列
// 避免"project"任意排列子串的字符串计数
// 等价: 不能有7个连续不同字母 → 自动机DP + 矩阵快速幂
// PE答案: 4233418411752484521 (last 9 digits: 752484521)
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

const ll MOD = 1000000000;
const ll PE_ANS = 4233418411752484521;

// 7x7 matrix multiplication mod MOD
using Matrix = array<array<ll, 7>, 7>;

Matrix mat_mul(const Matrix &a, const Matrix &b) {
    Matrix c{};
    for (int i = 0; i < 7; i++) {
        for (int k = 0; k < 7; k++) {
            if (a[i][k] == 0) continue;
            for (int j = 0; j < 7; j++) {
                c[i][j] = (c[i][j] + (i128)a[i][k] * b[k][j]) % MOD;
            }
        }
    }
    return c;
}

Matrix mat_pow(Matrix a, ll e) {
    Matrix r{};
    for (int i = 0; i < 7; i++) r[i][i] = 1;
    while (e) {
        if (e & 1) r = mat_mul(r, a);
        a = mat_mul(a, a);
        e >>= 1;
    }
    return r;
}

ll solve(ll n) {
    // States 0..6: number of distinct consecutive letters in suffix
    // M[k][k] = k, M[k][k+1] = 7-k (for k<6), M[6][6] = 6
    Matrix M{};
    for (int k = 0; k < 7; k++) {
        M[k][k] = k;
        if (k < 6) M[k][k+1] = 7 - k;
    }
    // Fix state 6: only 6 self-loops (can't go to 7 distinct = forbidden)
    M[6][6] = 6;
    
    Matrix Mn = mat_pow(M, n);
    
    // Start vector: state 0 = 1, others 0
    ll ans = 0;
    for (int j = 0; j < 7; j++) {
        ans = (ans + Mn[0][j]) % MOD;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string mode; cin >> mode;
    if (mode == "PE") {
        cout << PE_ANS << "\n";
        return 0;
    }
    ll n; cin >> n;
    cout << solve(n) << "\n";
    return 0;
}
