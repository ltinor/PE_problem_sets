#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M;
    cin >> M;

    vector<int> pent;
    for (int k = 1; ; k++) {
        int g1 = k * (3 * k - 1) / 2;
        if (g1 > 100000) break;
        pent.push_back(g1);
        int g2 = k * (3 * k + 1) / 2;
        if (g2 > 100000) break;
        pent.push_back(g2);
    }

    vector<int> p(1, 1 % M);

    int n = 0;
    while (true) {
        n++;
        ll val = 0;
        for (int i = 0; i < (int)pent.size() && pent[i] <= n; i++) {
            int sign = ((i / 2) % 2 == 0) ? 1 : -1;
            val = (val + sign * p[n - pent[i]]) % M;
        }
        val = (val % M + M) % M;
        p.push_back((int)val);
        if (val == 0) {
            cout << n << "\n";
            break;
        }
    }

    return 0;
}
