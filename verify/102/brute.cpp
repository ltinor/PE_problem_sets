#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Alternative implementation: area method
// Origin in triangle ABC iff area(ABC) = area(OAB) + area(OBC) + area(OCA)
ll twice_area(ll x1, ll y1, ll x2, ll y2, ll x3, ll y3) {
    return abs(x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2));
}

bool contains_origin_brute(ll ax, ll ay, ll bx, ll by, ll cx, ll cy) {
    ll total = twice_area(ax, ay, bx, by, cx, cy);
    ll oab = twice_area(0, 0, ax, ay, bx, by);
    ll obc = twice_area(0, 0, bx, by, cx, cy);
    ll oca = twice_area(0, 0, cx, cy, ax, ay);
    return total > 0 && (oab + obc + oca == total) && oab > 0 && obc > 0 && oca > 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    int ans = 0;
    for (int i = 0; i < N; i++) {
        ll x1, y1, x2, y2, x3, y3;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        if (contains_origin_brute(x1, y1, x2, y2, x3, y3))
            ans++;
    }

    cout << ans << "\n";
    return 0;
}
