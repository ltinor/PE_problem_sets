#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 906 暴力版：直接枚举所有 (n!)^3 个三元组，用线性扫描判断 Condorcet 胜者。
// 仅适用于很小的 n (n <= 5)，用于与 std 对拍。

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll n; cin >> n;

    vector<vector<int>> perms;
    vector<int> p(n);
    iota(p.begin(), p.end(), 0);
    do { perms.push_back(p); } while (next_permutation(p.begin(), p.end()));
    int P = perms.size();

    ll wins = 0;
    for (int a = 0; a < P; a++)
        for (int b = 0; b < P; b++)
            for (int c = 0; c < P; c++) {
                bool found = false;
                for (int i = 0; i < n && !found; i++) {
                    bool win = true;
                    for (int j = 0; j < n && win; j++) {
                        if (i == j) continue;
                        int cnt = 0;
                        for (int k = 0; k < n; k++) {
                            if (perms[a][k] == i) { cnt++; break; }
                            if (perms[a][k] == j) break;
                        }
                        for (int k = 0; k < n; k++) {
                            if (perms[b][k] == i) { cnt++; break; }
                            if (perms[b][k] == j) break;
                        }
                        for (int k = 0; k < n; k++) {
                            if (perms[c][k] == i) { cnt++; break; }
                            if (perms[c][k] == j) break;
                        }
                        if (cnt < 2) win = false;
                    }
                    if (win) found = true;
                }
                if (found) wins++;
            }

    ll nf = 1; for (ll i = 2; i <= n; i++) nf *= i;
    long double total = (long double)nf * nf * nf;
    cout << fixed << setprecision(10) << (double)((long double)wins / total) << "\n";
    return 0;
}
