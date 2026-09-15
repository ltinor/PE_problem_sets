#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Pentagon number theorem:
// p(n) = Σ (-1)^(k+1) * p(n - g(k))
// where g(k) = k*(3*k-1)/2 for k = 1, -1, 2, -2, 3, -3, ...

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M;
    cin >> M;

    // Pre-generate pentagon numbers
    vector<int> pent;
    for (int k = 1; ; k++) {
        int g1 = k * (3 * k - 1) / 2;
        if (g1 > 100000) break;
        pent.push_back(g1);
        int g2 = k * (3 * k + 1) / 2;
        if (g2 > 100000) break;
        pent.push_back(g2);
    }

    // p[n] mod M
    vector<int> p(1, 1 % M); // p[0] = 1 mod M

    int n = 0;
    while (true) {
        n++;
        ll val = 0;
        for (int i = 0; i < (int)pent.size() && pent[i] <= n; i++) {
            // Sign: + for i=0,4,8,... (k=1, -2, 3, -4...), - for i=1,3,5,7,... (k=-1, 2, -3, 4...)
            // i=0 -> k=1 -> sign + (odd k = +)
            // i=1 -> k=-1 -> sign + (consecutive -1)
            // Let's use: sign = (i/2 % 2 == 0) ? +1 : -1
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
