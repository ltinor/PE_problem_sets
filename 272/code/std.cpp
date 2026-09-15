#include<bits/stdc++.h>
using namespace std;

#define ll long long

// C(n) = ∏ c(p^e) - 1, c(p^e) = 3 if p≡1(mod 3) or (p=3,e≥2), else 1
// C(n) = K ⇒ ∏c = K+1 = 3^T
// n = A * M where A = product of T active prime powers, M = neutral part

ll N, K;
int T;
ll total_ans;

vector<ll> primes1;     // primes ≡ 1 (mod 3)
vector<ll> neutral;     // neutral numbers sorted

void gen_primes1() {
    // Upper bound for primes needed:
    // Largest prime ≤ N / (product of T-1 smallest primes ≡ 1 mod 3 or 3^2)
    ll bound = N;
    if (T >= 1) {
        // Compute product of T-1 smallest valid factors
        // Use 3^2 + (T-2) primes or T-1 primes, whichever gives larger bound
        ll prod9 = 9;
        ll prod_1 = 1;
        // We'll compute exact bound after initial sieve; use generous bound first
        bound = min(N, 20000000LL);
    }
    int L = (int)min(bound, 20000000LL);
    vector<bool> isp(L + 1, true);
    isp[0] = isp[1] = false;
    for (int i = 2; i <= L; i++) {
        if (isp[i]) {
            if (i % 3 == 1) primes1.push_back(i);
            if ((ll)i * i <= L) {
                for (ll j = (ll)i * i; j <= L; j += i) isp[j] = false;
            }
        }
    }
}

void gen_neutral(ll maxX) {
    // Neutral primes: p≡2 mod 3 (any exp) and 3^1
    vector<ll> np;
    np.push_back(3);
    int L = (int)min(maxX, 20000000LL);
    vector<bool> isp(L + 1, true);
    isp[0] = isp[1] = false;
    for (int i = 2; i <= L; i++) {
        if (isp[i]) {
            if (i % 3 == 2) np.push_back(i);
            if ((ll)i * i <= L) {
                for (ll j = (ll)i * i; j <= L; j += i) isp[j] = false;
            }
        }
    }
    
    set<ll> nums;
    function<void(int, ll)> dfs = [&](int idx, ll cur) {
        nums.insert(cur);
        if (idx >= (int)np.size()) return;
        ll p = np[idx];
        dfs(idx + 1, cur);
        int max_e = (p == 3) ? 1 : 60;
        ll pp = p;
        for (int e = 1; e <= max_e && cur <= maxX / pp; e++) {
            dfs(idx + 1, cur * pp);
            if (pp > maxX / p) break;
            pp *= p;
        }
    };
    dfs(0, 1);
    
    neutral.assign(nums.begin(), nums.end());
    sort(neutral.begin(), neutral.end());
}

ll sum_neutral(ll X, ll A) {
    ll sum = 0;
    for (ll m : neutral) {
        if (m > X) break;
        if (gcd(m, A) == 1) sum += m;
    }
    return sum;
}

void dfs_A(int start, int need, ll cur) {
    if (need == 0) {
        total_ans += cur * sum_neutral(N / cur, cur);
        return;
    }
    
    int remaining = (int)primes1.size() - start;
    if (remaining < need) return;
    
    for (int i = start; i <= (int)primes1.size() - need; i++) {
        ll p = primes1[i];
        if (p > N / cur) break;
        
        ll pp = p;
        while (cur <= N / pp) {
            dfs_A(i + 1, need - 1, cur * pp);
            if (pp > N / p) break;
            pp *= p;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> N >> K;
    
    ll val = K + 1;
    T = 0;
    while (val % 3 == 0) { val /= 3; T++; }
    if (val != 1 || T == 0) { cout << "0\n"; return 0; }
    
    gen_primes1();
    
    // Min A for computing maxX
    ll minA = 1;
    if (T > 0) {
        if ((int)primes1.size() >= T - 1) {
            ll prod = 9;
            for (int i = 0; i < T - 1; i++) prod *= primes1[i];
            minA = prod;
        }
        if ((int)primes1.size() >= T) {
            ll prod = 1;
            for (int i = 0; i < T; i++) prod *= primes1[i];
            if (prod < minA) minA = prod;
        }
    }
    ll maxX = N / max(1LL, minA);
    gen_neutral(maxX);
    
    total_ans = 0;
    
    // Without 3^e
    if ((int)primes1.size() >= T) {
        dfs_A(0, T, 1);
    }
    
    // With 3^e (e ≥ 2) + (T-1) primes
    if (T >= 1) {
        ll p3 = 9;
        while (p3 <= N) {
            if (T == 1) {
                total_ans += p3 * sum_neutral(N / p3, p3);
            } else if ((int)primes1.size() >= T - 1) {
                dfs_A(0, T - 1, p3);
            }
            if (p3 > N / 3) break;
            p3 *= 3;
        }
    }
    
    cout << total_ans << "\n";
    return 0;
}
