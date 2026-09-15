#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 100000000;

// 194: Colored unit chain
// Unit: 7 vertices (a,b,c,d,e,f,g), 9 edges
//   a-b, a-c, b-c, c-d, d-f, d-e, e-f, e-g, f-g
// Chain: share right boundary (b,g) with next unit's left (a,f)
// DP state = (color_top, color_bottom) on the shared boundary

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int A,B,C; cin>>A>>B>>C;
    if(C<=0 || A+B>100000){cout<<"0\n";return 0;}
    
    int S = C*C;
    vector<ll> trans(S*S, 0);
    auto idx = [&](int t, int b){ return t*C + b; };
    
    // Enumerate all colorings of one unit
    vector<pair<int,int>> edges = {{0,1},{0,2},{1,2},{2,3},{3,5},{3,4},{4,5},{4,6},{5,6}};
    // vertices: 0=a, 1=b, 2=c, 3=d, 4=e, 5=f, 6=g
    // Left boundary: a=0, f=5. Right boundary: b=1, g=6
    
    for(int a=0;a<C;a++)for(int b=0;b<C;b++)
    for(int c=0;c<C;c++)for(int d=0;d<C;d++)
    for(int e=0;e<C;e++)for(int f=0;f<C;f++)
    for(int g=0;g<C;g++){
        int cols[7]={a,b,c,d,e,f,g}; bool ok=1;
        for(auto& [u,v]:edges) if(cols[u]==cols[v]){ok=0;break;}
        if(!ok) continue;
        trans[idx(a,f)*S + idx(b,g)]++;
    }
    
    // Chain DP
    vector<ll> dp(S,0);
    // First unit: free left boundary
    for(int si=0;si<S;si++) for(int so=0;so<S;so++)
        dp[so] = (dp[so] + trans[si*S+so]) % MOD;
    
    // Remaining units (A+B-1 more)
    for(int i=1; i<A+B; i++){
        vector<ll> ndp(S,0);
        for(int si=0;si<S;si++){
            if(!dp[si]) continue;
            ll* row = &trans[si*S];
            for(int so=0;so<S;so++)
                ndp[so] = (ndp[so] + dp[si] * row[so]) % MOD;
        }
        dp = ndp;
    }
    
    ll ans = 0;
    for(int s=0;s<S;s++) ans = (ans + dp[s]) % MOD;
    cout << ans << "\n";
}
