#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Check if origin (0,0) is strictly inside triangle ABC
// Using cross product sign test: all three cross(O,A,B), cross(O,B,C), cross(O,C,A) same sign
bool contains_origin(ll ax, ll ay, ll bx, ll by, ll cx, ll cy) {
    auto cross = [](ll x1, ll y1, ll x2, ll y2) -> ll {
        return x1 * y2 - y1 * x2;
    };
    ll d1 = cross(ax, ay, bx, by);
    ll d2 = cross(bx, by, cx, cy);
    ll d3 = cross(cx, cy, ax, ay);
    // Origin is strictly inside if all have same sign and none is zero
    if (d1 == 0 || d2 == 0 || d3 == 0) return false;
    return (d1 > 0 && d2 > 0 && d3 > 0) || (d1 < 0 && d2 < 0 && d3 < 0);
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
        if (contains_origin(x1, y1, x2, y2, x3, y3))
            ans++;
    }

    cout << ans << "\n";
    return 0;
}
