#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// Brute force for PE502: enumerate castles for small w,h
// A castle: non-increasing heights, at least one even block height
int main() {
    string query;
    getline(cin, query);
    stringstream ss(query);
    ll w, h;
    ss >> w >> h;

    if (w > 6 || h > 6) {
        cout << "0\n";
        return 0;
    }

    ll ans = 0;
    // Enumerate all non-increasing sequences of length w, values 0..h
    vector<int> seq(w, 0);
    function<void(int, int)> dfs = [&](int pos, int max_val) {
        if (pos == w) {
            bool has_even = false;
            for (int v : seq) if (v > 0 && v % 2 == 0) has_even = true;
            if (has_even) ans++;
            return;
        }
        for (int v = max_val; v >= 0; v--) {
            seq[pos] = v;
            dfs(pos + 1, v);
        }
    };
    dfs(0, h);
    cout << ans << "\n";
}
