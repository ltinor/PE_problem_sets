#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int my_gcd_int(int a, int b) {
    a = a < 0 ? -a : a; b = b < 0 ? -b : b;
    while (b) { int t = b; b = a % b; a = t; }
    return a;
}

// PE415 brute: Titanic sets enumeration

bool is_titanic(ll mask, int N) {
    int total = (N+1)*(N+1);
    vector<pair<int,int>> pts;
    for (int i = 0; i < total; i++) {
        if (mask & (1LL << i)) {
            pts.push_back({i / (N+1), i % (N+1)});
        }
    }
    int m = pts.size();
    for (int i = 0; i < m; i++) {
        for (int j = i+1; j < m; j++) {
            int dx = pts[j].first - pts[i].first;
            int dy = pts[j].second - pts[i].second;
            int g = my_gcd_int(abs(dx), abs(dy));
            int sx = dx / g, sy = dy / g;
            int cnt = 0;
            for (int k = 0; k < m; k++) {
                int ex = pts[k].first - pts[i].first;
                int ey = pts[k].second - pts[i].second;
                if ((ll)ex * sy == (ll)ey * sx) {
                    if (sx != 0) { if (ex % sx == 0) cnt++; }
                    else if (sy != 0) { if (ey % sy == 0) cnt++; }
                    else cnt++;
                }
            }
            if (cnt == 2) return true;
        }
    }
    return false;
}

ll T_brute(ll N) {
    ll total = (N+1)*(N+1);
    if (total > 20) return 0;
    ll max_mask = 1LL << total;
    ll ans = 0;
    for (ll mask = 0; mask < max_mask; mask++) {
        if (is_titanic(mask, N)) ans++;
    }
    return ans % 100000000LL;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll N; cin >> N;
    cout << T_brute(N) << "\n";
}
