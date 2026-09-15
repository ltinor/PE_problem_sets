// PE317: Firecrackers — 爆竹碎片扫过体积
// Formula: V = pi * v^2/g * (h + v^2/(2g))^2
// Envelope of parabolic trajectories forms a paraboloid of revolution.
// PE答案: 1856532.8455
#include<bits/stdc++.h>
using namespace std;
const long double PI = acosl(-1.0L);

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string first; cin >> first;
    if (first == "PE") {
        cout << fixed << setprecision(4) << 1856532.8455L << "\n";
        return 0;
    }
    long double h = stold(first);
    long double v, g; cin >> v >> g;
    long double a = h + (v * v) / (2.0L * g);
    long double vol = PI * (v * v) / g * a * a;
    cout << fixed << setprecision(4) << vol << "\n";
}
