#include<bits/stdc++.h>
using namespace std;

#define ll long long

// extended gcd
ll egcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    ll g = egcd(b, a % b, y, x);
    y -= a / b * x;
    return g;
}

// modular inverse
ll inv(ll a, ll m) {
    ll x, y;
    egcd(a, m, x, y);
    return (x % m + m) % m;
}

// fast pow mod
ll mpow(ll a, ll e, ll m) {
    ll r = 1;
    while (e) {
        if (e & 1) r = (__int128)r * a % m;
        a = (__int128)a * a % m;
        e >>= 1;
    }
    return r;
}

// factor n
vector<pair<ll,int>> factor(ll n) {
    vector<pair<ll,int>> res;
    for (ll p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            int e = 0;
            while (n % p == 0) { n /= p; e++; }
            res.push_back({p, e});
        }
    }
    if (n > 1) res.push_back({n, 1});
    return res;
}

// find all solutions to x^3 ≡ 1 (mod p^e), return them in [0, p^e)
vector<ll> solve_prime_power(ll p, int e) {
    vector<ll> res;
    ll pe = 1;
    for (int i = 0; i < e; i++) pe *= p;
    
    if (p == 3) {
        if (e == 1) res = {1};
        else {
            // solutions mod 9: 1, 4, 7. Lift to 3^e.
            vector<ll> base = {1, 4, 7};
            ll cur_mod = 9;
            for (auto x : base) {
                ll cur = x;
                for (int k = 2; k < e; k++) {
                    // Hensel lift: x^3 ≡ 1 (mod 3^{k+1})
                    // f(cur) = cur^3 - 1, f'(cur) = 3*cur^2
                    // cur_{new} = cur - f(cur)/f'(cur) mod 3^{k+1}
                    // Actually: cur_{new} = cur + t * 3^k where t solves:
                    // (cur + t*3^k)^3 ≡ 1 (mod 3^{k+1})
                    // cur^3 + 3*cur^2*t*3^k ≡ 1 (mod 3^{k+1})
                    // t ≡ -(cur^3 - 1)/(3^{k+1}) * inv(cur^2) (mod 3)
                    ll cur_mod_k = 1;
                    for (int j = 0; j < k; j++) cur_mod_k *= 3;
                    ll cur_mod_k1 = cur_mod_k * 3;
                    ll f = (mpow(cur, 3, cur_mod_k1) - 1 + cur_mod_k1) % cur_mod_k1;
                    // f should be multiple of cur_mod_k
                    ll t = (f / cur_mod_k) % 3;
                    // We need: (cur^3 - 1)/3^k + 3*cur^2*t ≡ 0 (mod 3)
                    // cur^2 ≡ 1 (mod 3) for all solutions, so:
                    // (cur^3 - 1)/3^k + t ≡ 0 (mod 3)
                    // t ≡ -(cur^3 - 1)/3^k (mod 3)
                    ll val = (mpow(cur, 3, cur_mod_k1) - 1 + cur_mod_k1) % cur_mod_k1;
                    t = (3 - (val / cur_mod_k) % 3) % 3;
                    cur = cur + t * cur_mod_k;
                }
                res.push_back(cur % pe);
            }
        }
    } else if (p % 3 == 1) {
        // Find primitive cube root of unity mod p
        // x^3 ≡ 1 mod p, x ≠ 1
        // Solutions: 1, g^{(p-1)/3}, g^{2(p-1)/3} where g is primitive root
        // Or just brute force search for small p
        vector<ll> sols;
        for (ll x = 2; x < p; x++) {
            if (mpow(x, 3, p) == 1) {
                sols.push_back(x);
                if (sols.size() == 2) break;
            }
        }
        res.push_back(1);
        for (auto s : sols) {
            // Hensel lift
            ll cur = s;
            ll mod = p;
            for (int k = 1; k < e; k++) {
                ll nmod = mod * p;
                // f(cur) = cur^3 - 1
                ll f = (mpow(cur, 3, nmod) - 1 + nmod) % nmod;
                ll df = 3 * cur % p * cur % p; // 3*cur^2 mod p
                ll df_inv = inv(df % p, p);
                ll t = ((p - f / mod % p) * df_inv) % p;
                cur = cur + t * mod;
                mod = nmod;
            }
            res.push_back(cur % pe);
        }
    } else {
        // p ≡ 2 mod 3: only solution is 1
        res = {1};
    }
    return res;
}

// CRT combine
ll crt(const vector<ll> &a, const vector<ll> &m, ll M) {
    ll ans = 0;
    for (int i = 0; i < (int)a.size(); i++) {
        ll mi = M / m[i];
        ll inv_mi = inv(mi % m[i], m[i]);
        ans = (ans + (__int128)a[i] * mi % M * inv_mi) % M;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll N;
    cin >> N;
    
    auto fac = factor(N);
    
    vector<ll> mods;
    vector<vector<ll>> solutions;
    
    for (auto &[p, e] : fac) {
        ll pe = 1;
        for (int i = 0; i < e; i++) pe *= p;
        mods.push_back(pe);
        solutions.push_back(solve_prime_power(p, e));
    }
    
    // CRT: enumerate all combinations
    ll ans = 0;
    int num_factors = mods.size();
    vector<int> idx(num_factors, 0);
    
    function<void(int)> dfs = [&](int pos) {
        if (pos == num_factors) {
            vector<ll> a;
            for (int i = 0; i < num_factors; i++) {
                a.push_back(solutions[i][idx[i]]);
            }
            ll x = crt(a, mods, N);
            if (x > 1 && x < N) ans += x;
            return;
        }
        for (int i = 0; i < (int)solutions[pos].size(); i++) {
            idx[pos] = i;
            dfs(pos + 1);
        }
    };
    dfs(0);
    
    cout << ans << "\n";
    return 0;
}
