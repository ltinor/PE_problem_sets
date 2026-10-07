#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 215: Brute force - recursive enumeration (only for very small W, H)

int W, H;
ll ans = 0;

// Generate all gap masks
void gen_patterns(int pos, ll mask, vector<ll>& patterns) {
    if (pos == W) {
        patterns.push_back(mask);
        return;
    }
    if (pos > W) return;
    if (pos + 2 <= W) {
        int np = pos + 2;
        ll nm = mask;
        if (np < W) nm |= (1LL << np);
        gen_patterns(np, nm, patterns);
    }
    if (pos + 3 <= W) {
        int np = pos + 3;
        ll nm = mask;
        if (np < W) nm |= (1LL << np);
        gen_patterns(np, nm, patterns);
    }
}

// Recursively build walls
void dfs(int row, ll prev_mask) {
    if (row == H) {
        ans++;
        return;
    }

    vector<ll> patterns;
    gen_patterns(0, 0, patterns);

    for (ll mask : patterns) {
        if ((mask & prev_mask) == 0) {
            dfs(row + 1, mask);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> W >> H;

    ans = 0;
    dfs(0, 0); // prev_mask=0 means no restrictions for first row

    cout << ans << "\n";
}
