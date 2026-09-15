#include<bits/stdc++.h>
using namespace std;
#define ll long long

// brute: 同算法，用于小N验证
ll mygcd(ll a, ll b){
    a = abs(a); b = abs(b);
    while(b){ ll t = b; b = a % b; a = t; }
    return a;
}

struct Frac {
    ll num, den;
    Frac(ll n=0, ll d=1){
        if(d < 0){ n = -n; d = -d; }
        if(d == 0){ num = 0; den = 1; return; }
        ll g = mygcd(abs(n), d);
        num = n/g; den = d/g;
    }
    bool operator<(const Frac& o) const {
        return (__int128)num * o.den < (__int128)o.num * den;
    }
    bool operator==(const Frac& o) const {
        return num == o.num && den == o.den;
    }
};

struct Point {
    Frac x, y;
    Point(Frac xx={}, Frac yy={}) : x(xx), y(yy) {}
    bool operator<(const Point& o) const {
        if(x == o.x) return y < o.y;
        return x < o.x;
    }
};

ll cross(ll x1, ll y1, ll x2, ll y2, ll x3, ll y3){
    return (x2-x1)*(y3-y1) - (y2-y1)*(x3-x1);
}

vector<array<ll,4>> generate_segments(int N){
    vector<ll> t(N*4 + 1);
    ll s = 290797;
    for(int i=1; i<=N*4; i++){
        s = (s * s) % 50515093;
        t[i] = s % 500;
    }
    vector<array<ll,4>> segs(N);
    for(int i=0; i<N; i++){
        segs[i] = {t[4*i+1], t[4*i+2], t[4*i+3], t[4*i+4]};
    }
    return segs;
}

pair<bool,Point> true_intersection(ll x1, ll y1, ll x2, ll y2,
                                     ll x3, ll y3, ll x4, ll y4){
    ll c1 = cross(x1,y1,x2,y2,x3,y3);
    ll c2 = cross(x1,y1,x2,y2,x4,y4);
    ll c3 = cross(x3,y3,x4,y4,x1,y1);
    ll c4 = cross(x3,y3,x4,y4,x2,y2);

    if(!((c1 > 0 && c2 < 0) || (c1 < 0 && c2 > 0))) return {false, {}};
    if(!((c3 > 0 && c4 < 0) || (c3 < 0 && c4 > 0))) return {false, {}};

    ll denom = (x1-x2)*(y3-y4) - (y1-y2)*(x3-x4);
    if(denom == 0) return {false, {}};

    ll px_num = (x1*y2 - y1*x2)*(x3-x4) - (x1-x2)*(x3*y4 - y3*x4);
    ll py_num = (x1*y2 - y1*x2)*(y3-y4) - (y1-y2)*(x3*y4 - y3*x4);

    return {true, Point(Frac(px_num, denom), Frac(py_num, denom))};
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N; cin >> N;
    auto segs = generate_segments(N);
    set<Point> pts;
    for(int i=0; i<N; i++)
        for(int j=i+1; j<N; j++){
            auto [ok, p] = true_intersection(
                segs[i][0], segs[i][1], segs[i][2], segs[i][3],
                segs[j][0], segs[j][1], segs[j][2], segs[j][3]);
            if(ok) pts.insert(p);
        }
    cout << pts.size() << "\n";
}
