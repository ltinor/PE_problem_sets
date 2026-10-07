#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 210: Brute force - check all points for small r

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll r;
    cin >> r;

    ll ans = 0;
    ll cx = r / 4;
    ll cy = r / 4;

    for (ll x = -r; x <= r; x++) {
        for (ll y = -r; y <= r; y++) {
            if (llabs(x) + llabs(y) > r) continue;
            if (x == 0 && y == 0) continue; // O
            if (x == cx && y == cy) continue; // C
            if (x == y) continue; // collinear on y=x → angle = 180°, not obtuse (<180°)

            // Check obtuse
            bool obtuse = false;

            // Angle at O: dot(OB, OC) < 0
            if (x * cx + y * cy < 0) obtuse = true;

            // Angle at B: dot(BO, BC) < 0
            if (!obtuse) {
                ll box = -x, boy = -y; // O-B
                ll bcx = cx - x, bcy = cy - y; // C-B
                if (box * bcx + boy * bcy < 0) obtuse = true;
            }

            // Angle at C: dot(CO, CB) < 0
            if (!obtuse) {
                ll cox = -cx, coy = -cy; // O-C
                ll cbx = x - cx, cby = y - cy; // B-C
                if (cox * cbx + coy * cby < 0) obtuse = true;
            }

            if (obtuse) ans++;
        }
    }

    cout << ans << "\n";
    return 0;
}
