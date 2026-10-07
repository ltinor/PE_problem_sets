#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll gcdll(ll a, ll b){ return b ? gcdll(b, a % b) : a; }

// Pythagorean Polygons (Project Euler 292), reduced-data version.
//
// A "Pythagorean polygon" is a convex polygon with integer vertices and
// integer edge lengths (>=3 vertices, no three collinear).  P(N) counts such
// polygons (up to translation) with perimeter <= N.
//
// Key reduction: every edge is a vector (dx,dy) with dx^2+dy^2 a perfect
// square.  Writing each such vector as k * (a,b) where (a,b) is primitive
// (gcd(a,b)=1, a^2+b^2=c^2), a convex polygon corresponds bijectively to an
// assignment of multiplicities k_d >= 0 (one per primitive direction d) with
//   sum_d k_d * (a_d, b_d) = (0,0)          (closed polygon)
// and with >= 3 distinct directions used (otherwise it degenerates to a
// segment).  Sorting the chosen edges by angle yields exactly one convex
// polygon, and vice-versa.
//
// So we compute
//   C(N) = sum_{p=1..N} [x^0 y^0 z^p] prod_d 1/(1 - x^{a_d} y^{b_d} z^{c_d})
// via a 3D unbounded-knapsack DP, then subtract the degenerate 2-edge
// "segments": for every antipodal pair {d,-d} (primitive length c) there are
// floor(N/(2c)) of them (k*d + k*(-d), perimeter 2kc).

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;
    if(N < 1){ cout << 0 << "\n"; return 0; }

    // Primitive directions (a,b,c): gcd(a,b)=1, a^2+b^2=c^2, c <= N.
    vector<array<ll,3>> dirs;
    // Axis directions (length 1).
    dirs.push_back({1,0,1});
    dirs.push_back({-1,0,1});
    dirs.push_back({0,1,1});
    dirs.push_back({0,-1,1});

    // Primitive Pythagorean triples (0 < a < b, c <= N), plus their 8
    // sign/swap orientations.
    vector<ll> tripleC;  // one entry per primitive triple (for the segment term)
    for(ll a=1; a<=N; a++){
        for(ll b=a+1; b<=N; b++){
            ll c2 = a*a + b*b;
            ll c = (ll)sqrt((long double)c2);
            if(c*c == c2 && c <= N && gcdll(a,b) == 1){
                ll combos[8][2] = {{a,b},{a,-b},{-a,b},{-a,-b},
                                   {b,a},{b,-a},{-b,a},{-b,-a}};
                for(int i=0;i<8;i++)
                    dirs.push_back({combos[i][0], combos[i][1], c});
                tripleC.push_back(c);
            }
        }
    }

    ll OFF = N;
    ll M = 2*N + 1;
    ll P = N + 1;
    // dp[(x,y,p)] = number of multisets of processed edges with vector sum
    // (x,y) and perimeter p.  Index: p * M*M + (x+OFF)*M + (y+OFF).
    vector<ll> dp(M*M*P, 0);
    auto idx = [&](ll x, ll y, ll p){ return p*M*M + (x+OFF)*M + (y+OFF); };
    dp[idx(0,0,0)] = 1;

    for(auto &d : dirs){
        ll a = d[0], b = d[1], c = d[2];
        // Unbounded knapsack along the ray (a,b,c).  Since c >= 1, the
        // dependency graph is ordered by perimeter: dp[x][y][p] only reads
        // dp[x-a][y-b][p-c] (a strictly smaller p), so a plain increasing-p
        // scan is a valid topological order (x/y order within a level is free).
        for(ll p=c; p<=N; p++){
            for(ll x=-N; x<=N; x++){
                ll px = x - a;
                if(px < -N || px > N) continue;
                for(ll y=-N; y<=N; y++){
                    ll py = y - b;
                    if(py < -N || py > N) continue;
                    dp[idx(x,y,p)] += dp[idx(px,py,p-c)];
                }
            }
        }
    }

    // C(N): closed configurations with perimeter 1..N.
    ll C = 0;
    for(ll p=1; p<=N; p++) C += dp[idx(0,0,p)];

    // S(N): degenerate two-edge "segments" (antipodal pairs, back and forth).
    ll S = 2 * (N / 2);              // axis pairs {(1,0),(-1,0)}, {(0,1),(0,-1)}
    for(ll c : tripleC) S += 4 * (N / (2*c));  // 4 antipodal pairs per triple

    cout << (C - S) << "\n";
    return 0;
}
