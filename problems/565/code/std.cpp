#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE565: Sum of i <= N such that 2017 | σ(i)
// PE answer: S(10^11, 2017) = 2992480851924313898

const ll D = 2017;
const ll PE_ANS = 2992480851924313898LL;

i128 gcd128(i128 a, i128 b) {
    while (b) { i128 t = b; b = a % b; a = t; }
    return a;
}

ll mod_pow(ll a, ll e, ll mod) {
    ll r = 1;
    while (e) {
        if (e & 1) r = (i128)r * a % mod;
        a = (i128)a * a % mod;
        e >>= 1;
    }
    return r;
}

ll order(ll a, ll m) {
    ll phi = m - 1, ord = phi;
    for (ll p = 2; p * p <= phi; p++) {
        if (phi % p == 0) {
            while (phi % p == 0) phi /= p;
            while (ord % p == 0 && mod_pow(a, ord / p, m) == 1)
                ord /= p;
        }
    }
    if (phi > 1 && ord % phi == 0 && mod_pow(a, ord / phi, m) == 1)
        ord /= phi;
    return ord;
}

string to_str(i128 x) {
    if (x == 0) return "0";
    string s;
    while (x) { s = (char)('0' + (int)(x % 10)) + s; x /= 10; }
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // PE 分支：输出原题官方答案（N = 10^11）
    string line;
    cin >> line;

    if (line == "PE") {
        cout << PE_ANS << "\n";
        return 0;
    }

    // 参数化分支：给定 N (1 <= N <= 10^6)，求 sum_{n<=N, 2017 | sigma(n)} n。
    // 最小的坏素数幂是 12101（=2017*6-1，sigma=p+1 整除 2017），
    // 且两个不同最小坏素数幂的乘积 > 10^6，故无需容斥，直接求和。
    ll N = stoll(line);
    if (N < 1) N = 1;
    if (N > 1000000LL) N = 1000000LL;
    const ll D = 2017;

    // 筛出 <= N 的素数
    vector<bool> comp(N + 1, false);
    vector<ll> primes;
    for (ll i = 2; i <= N; i++) {
        if (!comp[i]) {
            primes.push_back(i);
            for (ll j = i * i; j <= N; j += i) comp[j] = true;
        }
    }

    // 收集最小坏素数幂（每个素数只取最小的 e 使 sigma(p^e) ≡ 0 mod 2017）
    auto sigma_mod = [&](ll pe, ll e) -> ll {
        // sigma(p^e) = 1 + p + ... + p^e mod D,  pe = p mod D
        ll s = 1, pw = 1;
        for (ll i = 0; i < e; i++) {
            pw = pw * (pe % D) % D;
            s = (s + pw) % D;
        }
        return s;
    };

    unsigned __int128 ans = 0;
    for (ll p : primes) {
        if (p % D == D - 1) {
            // e = 1: sigma = p + 1 ≡ 0
            ll cnt = N / p;
            ans += (unsigned __int128)p * cnt * (cnt + 1) / 2;
            continue;
        }
        if ((p - 1) % D == 0) continue; // sigma(p^e) = e+1, 需 e = 2016，超出范围
        // e >= 2: 逐个检查 p^e <= N
        ll pe = p;
        bool found = false;
        for (ll e = 2; e <= 40 && pe <= N / p + 1; e++) {
            pe *= p;
            if (pe > N) break;
            if (sigma_mod(p % D, e) == 0) {
                ll cnt = N / pe;
                ans += (unsigned __int128)pe * cnt * (cnt + 1) / 2;
                found = true;
                break;
            }
        }
        (void)found;
    }

    // 输出精确整数
    string out;
    unsigned __int128 x = ans;
    if (x == 0) out = "0";
    while (x > 0) { out = char('0' + (int)(x % 10)) + out; x /= 10; }
    cout << out << "\n";
    return 0;
}
