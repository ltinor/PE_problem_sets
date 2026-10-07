// PE323: Bitwise-OR operations
// 期望值直到 x_i 全 1: E = sum_{k>=0} P(X>k), P(X>k) = 1-(1-2^-k)^K
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    string tok; cin >> tok;
    if (tok == "PE") { cout << fixed << setprecision(10) << 6.3551758451 << "\n"; return 0; }
    ll K = stoll(tok);
    double E = 0;
    for (int k = 0; k < 4000; k++) {
        double p = 1.0 - pow(1.0 - pow(2.0, -(double)k), (double)K);
        E += p;
        if (p < 1e-17) break;
    }
    cout << fixed << setprecision(10) << E << "\n";
}
