// PE459: Flipping Game — 翻转游戏 (optimized)
// N×N棋盘，翻转游戏。宽度平方数，高度三角数。
// 致胜第一步计数: XOR over flipped rectangle = 0
// PE答案: 3996390106631
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const ll PE_ANS = 3996390106631;

vector<int> compute_grundy(int N, const vector<int> &lengths) {
    vector<int> g(N+1, 0), pref(N+1, 0);
    for (int i = 1; i <= N; i++) {
        bool seen[8] = {};
        for (int l : lengths) {
            if (l > i) break;
            int x = pref[i-1] ^ pref[i-l];
            if (x < 8) seen[x] = true;
        }
        int mex = 0;
        while (mex < 8 && seen[mex]) mex++;
        g[i] = mex;
        pref[i] = pref[i-1] ^ mex;
    }
    return g;
}

ll solve(int N) {
    // Square lengths
    vector<int> squares;
    for (int i = 1; i * i <= N; i++) squares.push_back(i * i);
    
    // Triangular lengths
    vector<int> triangs;
    for (int i = 1; ; i++) {
        int t = i * (i + 1) / 2;
        if (t > N) break;
        triangs.push_back(t);
    }
    
    auto gS = compute_grundy(N, squares);
    auto gT = compute_grundy(N, triangs);
    
    vector<int> prefS(N+1, 0), prefT(N+1, 0);
    for (int i = 1; i <= N; i++) {
        prefS[i] = prefS[i-1] ^ gS[i];
        prefT[i] = prefT[i-1] ^ gT[i];
    }
    
    // Precompute counts for each w (square) and v
    // cntS[w_idx][v] = number of x in [w, N] with prefS[x]^prefS[x-w] = v
    int NS = squares.size();
    int NT = triangs.size();
    vector<vector<ll>> cntS(NS, vector<ll>(8, 0));
    vector<vector<ll>> cntT(NT, vector<ll>(8, 0));
    vector<ll> cntS_zero(NS, 0), cntT_zero(NT, 0); // v=0 count
    
    // Compute cntS
    for (int si = 0; si < NS; si++) {
        int w = squares[si];
        for (int x = w; x <= N; x++) {
            int v = prefS[x] ^ prefS[x-w];
            cntS[si][v]++;
        }
        cntS_zero[si] = cntS[si][0];
    }
    
    // Compute cntT
    for (int ti = 0; ti < NT; ti++) {
        int h = triangs[ti];
        for (int y = h; y <= N; y++) {
            int v = prefT[y] ^ prefT[y-h];
            cntT[ti][v]++;
        }
        cntT_zero[ti] = cntT[ti][0];
    }
    
    ll ans = 0;
    
    for (int si = 0; si < NS; si++) {
        int w = squares[si];
        ll Nw = N - w + 1;
        bool w_odd = w & 1;
        
        for (int ti = 0; ti < NT; ti++) {
            int h = triangs[ti];
            ll Nh = N - h + 1;
            bool h_odd = h & 1;
            
            ll contrib;
            if (!w_odd && !h_odd) {
                contrib = Nw * Nh;
            } else if (!w_odd) {
                contrib = cntS_zero[si] * Nh;
            } else if (!h_odd) {
                contrib = Nw * cntT_zero[ti];
            } else {
                contrib = 0;
                for (int v = 0; v < 8; v++) {
                    contrib += cntS[si][v] * cntT[ti][v];
                }
            }
            ans += contrib;
        }
    }
    
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string mode; cin >> mode;
    if (mode == "PE") {
        cout << PE_ANS << "\n";
        return 0;
    }
    int n; cin >> n;
    cout << solve(n) << "\n";
    return 0;
}
