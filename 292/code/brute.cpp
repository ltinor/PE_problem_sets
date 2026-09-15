#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll gcdll(ll a, ll b){ return b ? gcdll(b, a % b) : a; }

// Independent brute-force reference for small N (N <= 8).
//
// Enumerates, by exhaustive recursion, every assignment of multiplicities
// k_d >= 0 (one per primitive Pythagorean direction d) such that the chosen
// edges close up (sum_d k_d * (a_d,b_d) = (0,0)) and at least 3 distinct
// directions are used.  By the same reduction used in std.cpp, each such
// assignment is exactly one convex Pythagorean polygon (degenerate 2-edge
// "segments" are excluded by requiring >= 3 directions).
//
// This is O( prod_d (N/c_d + 1) ) and only runs for small N; for larger N it
// prints -1 so the harness knows to skip it.

ll N;
vector<array<ll,3>> dirs;
ll ans = 0;

void dfs(int idx, ll x, ll y, ll p, int used){
    if(idx == (int)dirs.size()){
        if(x == 0 && y == 0 && p >= 1 && p <= N && used >= 3) ans++;
        return;
    }
    ll a = dirs[idx][0], b = dirs[idx][1], c = dirs[idx][2];
    ll maxk = N / c;
    for(ll k = 0; k <= maxk; k++){
        ll np = p + k*c;
        if(np > N) break;
        ll nx = x + k*a, ny = y + k*b;
        if(nx < -N || nx > N || ny < -N || ny > N) continue;
        dfs(idx+1, nx, ny, np, used + (k > 0));
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    if(N < 1){ cout << 0 << "\n"; return 0; }
    if(N > 8){ cout << -1 << "\n"; return 0; } // too large for exhaustive search

    dirs.push_back({1,0,1});
    dirs.push_back({-1,0,1});
    dirs.push_back({0,1,1});
    dirs.push_back({0,-1,1});
    for(ll a = 1; a <= N; a++){
        for(ll b = a+1; b <= N; b++){
            ll c2 = a*a + b*b;
            ll c = (ll)sqrt((long double)c2);
            if(c*c == c2 && c <= N && gcdll(a,b) == 1){
                ll combos[8][2] = {{a,b},{a,-b},{-a,b},{-a,-b},
                                   {b,a},{b,-a},{-b,a},{-b,-a}};
                for(int i = 0; i < 8; i++)
                    dirs.push_back({combos[i][0], combos[i][1], c});
            }
        }
    }

    dfs(0, 0, 0, 0, 0);
    cout << ans << "\n";
    return 0;
}
