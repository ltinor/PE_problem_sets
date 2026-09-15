#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE453 brute: enumerate all 4-point combinations
ll Q_brute(ll m, ll n) {
    if (m > 6 || n > 6) return -1;
    vector<pair<ll,ll>> pts;
    for (ll x = 0; x <= m; x++)
        for (ll y = 0; y <= n; y++)
            pts.push_back({x,y});
    
    int P = pts.size();
    ll cnt = 0;
    
    for (int a = 0; a < P; a++)
    for (int b = a+1; b < P; b++)
    for (int c = b+1; c < P; c++)
    for (int d = c+1; d < P; d++) {
        auto cross = [&](int i, int j, int k) -> ll {
            ll x1 = pts[j].first - pts[i].first;
            ll y1 = pts[j].second - pts[i].second;
            ll x2 = pts[k].first - pts[i].first;
            ll y2 = pts[k].second - pts[i].second;
            return x1*y2 - x2*y1;
        };
        if (cross(a,b,c)==0 || cross(a,b,d)==0 || cross(a,c,d)==0 || cross(b,c,d)==0) continue;
        
        ll s1=cross(a,b,c), s2=cross(b,c,d), s3=cross(c,d,a), s4=cross(d,a,b);
        bool convex = (s1>0&&s2>0&&s3>0&&s4>0) || (s1<0&&s2<0&&s3<0&&s4<0);
        
        auto in_tri = [&](int p, int t1, int t2, int t3) {
            ll x=pts[p].first, y=pts[p].second;
            ll x1=pts[t1].first, y1=pts[t1].second;
            ll x2=pts[t2].first, y2=pts[t2].second;
            ll x3=pts[t3].first, y3=pts[t3].second;
            auto sgn = [](ll a,ll b,ll c,ll d,ll e,ll f){return (a-e)*(d-f)-(c-e)*(b-f);};
            ll d1=sgn(x,y,x1,y1,x2,y2), d2=sgn(x,y,x2,y2,x3,y3), d3=sgn(x,y,x3,y3,x1,y1);
            return !((d1<0||d2<0||d3<0) && (d1>0||d2>0||d3>0));
        };
        bool concave = in_tri(a,b,c,d)||in_tri(b,a,c,d)||in_tri(c,a,b,d)||in_tri(d,a,b,c);
        if (convex||concave) cnt++;
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll m, n; cin >> m >> n;
    ll ans = Q_brute(m, n);
    cout << ans << "\n";
}
