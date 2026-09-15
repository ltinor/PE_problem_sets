#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Fsf(n): number of ways to factor n into squarefree factors > 1
// For prime p_i with exponent e_i: assign e_i indistinguishable copies
// to distinct factors. For j factors: C(j, e_i) ways per prime.
// Inclusion-exclusion for nonempty factors:
// Fsf(n) = sum_{m} (1/m!) sum_{j} (-1)^{m-j} C(m,j) ∏ C(j, e_i)

// Parameterized: input N, output S(N) mod M

ll MOD;
vector<ll> fact, inv_fact;

ll modpow(ll a, ll e) {
    ll r = 1;
    while (e) { if (e&1) r=r*a%MOD; a=a*a%MOD; e>>=1; }
    return r;
}

void precompute(int n) {
    fact.resize(n+1); inv_fact.resize(n+1);
    fact[0]=1;
    for(int i=1;i<=n;i++) fact[i]=fact[i-1]*i%MOD;
    inv_fact[n]=modpow(fact[n],MOD-2);
    for(int i=n;i>=1;i--) inv_fact[i-1]=inv_fact[i]*i%MOD;
}

ll nCr(int n, int r) {
    if(r<0||r>n) return 0;
    return fact[n]*inv_fact[r]%MOD*inv_fact[n-r]%MOD;
}

ll Fsf_compute(const vector<int>& exps) {
    if(exps.empty()) return 0;
    int k=exps.size();
    int max_e=*max_element(exps.begin(),exps.end());
    int sum_e=accumulate(exps.begin(),exps.end(),0);
    
    ll total=0;
    for(int m=max_e; m<=sum_e; m++) {
        ll term=0;
        for(int j=0; j<=m; j++) {
            ll prod=1;
            for(int i=0; i<k; i++)
                prod=prod*nCr(j, exps[i])%MOD;
            ll contrib=nCr(m,j)*prod%MOD;
            if((m-j)&1) term=(term-contrib+MOD)%MOD;
            else term=(term+contrib)%MOD;
        }
        term=term*inv_fact[m]%MOD;
        total=(total+term)%MOD;
    }
    return total;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll N;
    cin >> N;
    MOD = 1000000007;
    
    precompute(N+5);
    
    vector<int> spf(N+1);
    for(int i=2; i<=N; i++) {
        if(spf[i]==0) {
            spf[i]=i;
            if((ll)i*i<=N)
                for(int j=i*i; j<=N; j+=i)
                    if(spf[j]==0) spf[j]=i;
        }
    }
    
    ll total=0;
    for(int n=2; n<=N; n++) {
        int x=n;
        map<int,int> fac;
        while(x>1) { fac[spf[x]]++; x/=spf[x]; }
        vector<int> exps;
        for(auto& kv:fac) exps.push_back(kv.second);
        sort(exps.rbegin(), exps.rend());
        total=(total+Fsf_compute(exps))%MOD;
    }
    
    cout << total << "\n";
    return 0;
}
