#include<bits/stdc++.h>
using namespace std;
#define ll long long

// a^2 + b^2 = c^2 + 1, a <= b <= c, perimeter a+b+c <= N
// (c-b)(c+b) = a^2 - 1 = (a-1)(a+1)
// Let u = c-b, v = c+b. uv = a^2-1, u <= v, u ≡ v (mod 2)
// c = (u+v)/2, b = (v-u)/2
// Need a <= b, and a+b+c = a+v <= N
// Also a+1 = a+v => v <= N-a
// Count for each a: divisors u of a^2-1 with u <= v, same parity, v <= N-a, a <= (v-u)/2

const int MAX_N = 25000000;

vector<int> spf;

void sieve(int n) {
    spf.assign(n + 1, 0);
    for(int i = 2; i <= n; i++) {
        if(spf[i] == 0) {
            spf[i] = i;
            if((ll)i * i <= n) {
                for(int j = i * i; j <= n; j += i) {
                    if(spf[j] == 0) spf[j] = i;
                }
            }
        }
    }
}

// Get prime factorization of x using SPF
vector<pair<ll,int>> factorize(int x) {
    vector<pair<ll,int>> res;
    while(x > 1) {
        int p = spf[x];
        int cnt = 0;
        while(x % p == 0) x /= p, cnt++;
        res.push_back({p, cnt});
    }
    return res;
}

// Generate all divisors from prime factorization
void gen_divisors(const vector<pair<ll,int>>& fac, int idx, ll cur, vector<ll>& divs) {
    if(idx == (int)fac.size()) {
        divs.push_back(cur);
        return;
    }
    ll p = fac[idx].first;
    int e = fac[idx].second;
    ll mul = 1;
    for(int i = 0; i <= e; i++) {
        gen_divisors(fac, idx+1, cur * mul, divs);
        mul *= p;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    // For a^2-1, we need a up to N/3 (since a <= b <= c and a+b+c <= N)
    ll maxA = N / 3;
    if(maxA < 2) { cout << "0\n"; return 0; }

    // SPF sieve up to N (for factorizing a-1, a+1)
    // But a^2-1 can be up to N^2/9, so we factor a-1 and a+1 separately
    sieve((int)N);

    ll ans = 0;

    for(ll a = 2; a <= maxA; a++) {
        auto fac1 = factorize(a - 1);
        auto fac2 = factorize(a + 1);

        // Merge factorizations (add exponents)
        map<ll,int> merged;
        for(auto &fp : fac1) merged[fp.first] += fp.second;
        for(auto &fp : fac2) merged[fp.first] += fp.second;

        vector<pair<ll,int>> fac;
        for(auto &p : merged) fac.push_back(p);

        vector<ll> divs;
        gen_divisors(fac, 0, 1, divs);

        for(ll u : divs) {
            ll v = (a*a - 1) / u;
            if(u > v) continue;
            // Check same parity: u and v must have same parity
            if((u & 1) != (v & 1)) continue;
            // c = (u+v)/2, b = (v-u)/2
            // Need a <= b => 2a <= v-u => v-u >= 2a
            if(v - u < 2 * a) continue;
            // Need a + v <= N
            if(a + v > N) continue;
            ans++;
        }
    }

    cout << ans << "\n";
    return 0;
}
