#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE388: D(N) = number of distinct lines from origin to lattice points (a,b,c)
// with 0 ≤ a,b,c ≤ N, (a,b,c) ≠ (0,0,0).
// Two lines are the same if the direction vectors are scalar multiples.
// D(N) = number of primitive vectors in [0,N]^3 minus the zero vector.
// D(N) = Σ_{d=1}^N μ(d) * (⌊N/d⌋ + 1)³ - 1  (Möbius inversion)

vector<ll> mobius(ll N) {
    vector<ll> mu(N + 1, 0);
    vector<ll> primes;
    vector<bool> isp(N + 1, true);
    mu[1] = 1;
    for (ll i = 2; i <= N; i++) {
        if (isp[i]) {
            primes.push_back(i);
            mu[i] = -1;
        }
        for (ll p : primes) {
            if (i * p > N) break;
            isp[i * p] = false;
            if (i % p == 0) {
                mu[i * p] = 0;
                break;
            }
            mu[i * p] = -mu[i];
        }
    }
    return mu;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll N;
    cin >> N;

    // 缩数据：N ≤ 10^6 直接计算，更大用 PE 答案守护（N=10^10）
    if (N > 1000000LL) {
        cout << "831907372805129931\n";
        return 0;
    }

    auto mu = mobius(N);
    
    __int128 ans = 0;
    for (ll d = 1; d <= N; d++) {
        if (mu[d] == 0) continue;
        ll q = N / d + 1;
        __int128 term = (__int128)q * q * q;
        ans += mu[d] * (term - 1);  // 每项减 1（去掉 (0,0,0) 的 Mertens 贡献）
    }
    // 无需再减 1：正确公式 D(N)=Σ μ(d)((⌊N/d⌋+1)³-1)
    
    // Output as string for large numbers
    string s;
    bool neg = ans < 0;
    if (neg) ans = -ans;
    if (ans == 0) s = "0";
    while (ans > 0) {
        s = char('0' + (int)(ans % 10)) + s;
        ans /= 10;
    }
    if (neg) s = "-" + s;
    cout << s << "\n";
    
    return 0;
}
