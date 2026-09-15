// PE440: GCD and Tiling — GCD与铺砖
// T(n) = 10*T(n-1) + T(n-2), T(0)=1, T(1)=10
// T(n) = U_{n+1}(10,-1): gcd(T(m),T(n)) = T(gcd(m+1,n+1)-1)
// gcd(c^a+1, c^b+1) = c^{gcd(a,b)}+1 if a/gcd & b/gcd both odd, else 1 or 2
// S(L) = Σ_d cnt_d * Σ_c T(c^d) + (L^2 - Σ cnt_d) * base_sum
// PE答案: 970746056
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

const ll MOD = 987898789;
const ll PE_ANS = 970746056;

// Matrix for T(n): [T(n+1); T(n)] = M * [T(n); T(n-1)]
// M = [[10, 1], [1, 0]]
// [T(n); T(n-1)] = M^{n-1} * [T(1); T(0)] for n>=1

struct Mat { ll a[2][2]; };

Mat mul(const Mat &x, const Mat &y) {
    Mat r{};
    r.a[0][0] = ((i128)x.a[0][0]*y.a[0][0] + (i128)x.a[0][1]*y.a[1][0]) % MOD;
    r.a[0][1] = ((i128)x.a[0][0]*y.a[0][1] + (i128)x.a[0][1]*y.a[1][1]) % MOD;
    r.a[1][0] = ((i128)x.a[1][0]*y.a[0][0] + (i128)x.a[1][1]*y.a[1][0]) % MOD;
    r.a[1][1] = ((i128)x.a[1][0]*y.a[0][1] + (i128)x.a[1][1]*y.a[1][1]) % MOD;
    return r;
}

Mat mpow(Mat a, ll e) {
    Mat r = {1,0,0,1};
    while (e) {
        if (e&1) r = mul(r, a);
        a = mul(a, a);
        e >>= 1;
    }
    return r;
}

ll T_val(ll n) {
    if (n == 0) return 1 % MOD;
    if (n == 1) return 10 % MOD;
    Mat M = {10%MOD, 1, 1, 0};
    Mat Mn = mpow(M, n-1);
    return ((i128)Mn.a[0][0]*10 + Mn.a[0][1]) % MOD;
}

// GCD function
ll gcd(ll a, ll b) { return b ? gcd(b, a%b) : a; }

ll solve(ll L) {
    // Precompute cnt_d: number of pairs (A,B) in [1, M] with gcd(A,B)=1, A odd, B odd
    // where M = L/d
    vector<ll> cnt_d(L+1);
    for (ll d = 1; d <= L; d++) {
        ll M = L / d;
        ll cnt = 0;
        for (ll A = 1; A <= M; A += 2) {
            for (ll B = 1; B <= M; B += 2) {
                if (gcd(A, B) == 1) cnt++;
            }
        }
        cnt_d[d] = cnt;
    }
    
    // Precompute T(c^d) for all c,d ≤ L
    // Use iterative approach: for each c, compute T(c), T(c^2), ..., T(c^L)
    vector<vector<ll>> T_pow(L+1, vector<ll>(L+1));
    for (ll c = 1; c <= L; c++) {
        // Compute T(c), T(c^2), ..., T(c^L)
        // T(c^1) = T(c)
        T_pow[c][1] = T_val(c);
        // For k>=2, we can't easily get c^k from c^{k-1} due to huge exponents
        // But we CAN use the matrix: M^{c^k} = (M^{c^{k-1}})^c
        // And T(c^k) = (M^{c^k-1} * [10;1])[0]
        Mat Mbase = {10%MOD, 1, 1, 0};
        Mat Minv = {0, 1, 1, (MOD-10)%MOD}; // M^{-1} (works mod MOD)
        
        Mat cur = mpow(Mbase, c);  // M^c
        for (ll k = 1; k <= L; k++) {
            // M^{c^k-1} = M^{c^k} * M^{-1}
            Mat Mm1 = mul(cur, Minv);
            T_pow[c][k] = ((i128)Mm1.a[0][0]*10 + Mm1.a[0][1]) % MOD;
            if (k < L) cur = mpow(cur, c);  // M^{c^{k+1}}
        }
    }
    
    // T_sum[d] = Σ_{c=1}^L T(c^d)
    vector<ll> T_sum(L+1);
    for (ll d = 1; d <= L; d++) {
        i128 s = 0;
        for (ll c = 1; c <= L; c++) {
            s += T_pow[c][d];
        }
        T_sum[d] = s % MOD;
    }
    
    // base_sum = Σ_{c=1}^L (c odd ? T(1) : T(0))
    i128 base = 0;
    for (ll c = 1; c <= L; c++) {
        base += (c & 1) ? T_val(1) : T_val(0);
    }
    base %= MOD;
    
    i128 ans = 0;
    i128 total_cnt = 0;
    for (ll d = 1; d <= L; d++) {
        ans = (ans + (i128)cnt_d[d] * T_sum[d]) % MOD;
        total_cnt += cnt_d[d];
    }
    ll other = (L*L - total_cnt) % MOD;
    ans = (ans + (i128)other * base) % MOD;
    
    return (ll)((ans % MOD + MOD) % MOD);
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
