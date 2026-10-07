#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 1000000007;

// PE408: Admissible paths through a grid
// 不容许点 (x,y): x, y, x+y 都是正平方数，即 x=a^2, y=b^2, a^2+b^2=c^2 (勾股三元组)。
// 从 (0,0) 到 (n,n) 的北/东路径，避开所有不容许点。
// 容斥 DP：dp[i] = 起点到障碍 i 的合法路径数（不经过其他障碍）。
// 验证：P(5)=252, P(16)=596994440, P(1000) mod 1e9+7 = 341920854。
// 答案：P(10^7) mod 1e9+7 = 299742733。

vector<ll> fact, inv_fact;

ll qpow(ll a, ll b){ ll r=1; while(b){ if(b&1) r=r*a%MOD; a=a*a%MOD; b>>=1; } return r; }

ll comb(int m, int k){
    if(k<0 || k>m) return 0;
    return fact[m] * inv_fact[k] % MOD * inv_fact[m-k] % MOD;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    ll n;
    cin >> n;

    // 预计算阶乘到 2n
    int maxm = (int)(2*n);
    fact.assign(maxm+1, 1);
    for(int i=1; i<=maxm; i++) fact[i] = fact[i-1] * i % MOD;
    inv_fact.assign(maxm+1, 1);
    inv_fact[maxm] = qpow(fact[maxm], MOD-2);
    for(int i=maxm; i>=1; i--) inv_fact[i-1] = inv_fact[i] * i % MOD;

    // 枚举勾股三元组 a^2+b^2=c^2，生成不容许点 (a^2,b^2) 和 (b^2,a^2)
    int maxa = (int)sqrt((long double)n);
    vector<pair<ll,ll>> obs;
    set<pair<ll,ll>> seen;
    for(ll a=1; a<=maxa; a++){
        ll a2 = a*a;
        for(ll b=1; b<=maxa; b++){
            ll b2 = b*b;
            ll c2 = a2 + b2;
            ll c = (ll)sqrt((long double)c2);
            while(c*c < c2) c++;
            while(c*c > c2) c--;
            if(c*c == c2){
                if(a2<=n && b2<=n){
                    for(auto p : {make_pair(a2,b2), make_pair(b2,a2)})
                        if(!seen.count(p)){ seen.insert(p); obs.push_back(p); }
                }
            }
        }
    }

    // 排序按 x+y 然后 x
    sort(obs.begin(), obs.end(), [](auto&A, auto&B){
        if(A.first+A.second != B.first+B.second) return A.first+A.second < B.first+B.second;
        return A.first < B.first;
    });

    int k = obs.size();
    vector<ll> dp(k, 0);
    for(int i=0; i<k; i++){
        ll xi=obs[i].first, yi=obs[i].second;
        ll total = comb((int)(xi+yi), (int)xi);
        for(int j=0; j<i; j++){
            ll xj=obs[j].first, yj=obs[j].second;
            if(xj<=xi && yj<=yi){
                total = (total - dp[j]*comb((int)((xi-xj)+(yi-yj)), (int)(xi-xj)) % MOD + MOD) % MOD;
            }
        }
        dp[i] = total;
    }

    ll ans = comb((int)(2*n), (int)n);
    for(int i=0; i<k; i++){
        ll xi=obs[i].first, yi=obs[i].second;
        ans = (ans - dp[i]*comb((int)((n-xi)+(n-yi)), (int)(n-xi)) % MOD + MOD) % MOD;
    }
    cout << ans << "\n";
    return 0;
}
