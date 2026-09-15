#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

// Brute force: for small a, enumerate n to find rmax
ull brute_rmax(int a) {
    ull a2 = 1ULL * a * a;
    ull best = 0;
    // n cycles with period depending on a; checking up to a*2 is enough
    for (int n = 1; n <= 2 * a; n++) {
        ull val = 0;
        // compute (a-1)^n + (a+1)^n mod a^2
        ull t1 = 1, t2 = 1;
        for (int k = 0; k < n; k++) {
            t1 = (t1 * (a - 1)) % a2;
            t2 = (t2 * (a + 1)) % a2;
        }
        val = (t1 + t2) % a2;
        if (val > best) best = val;
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int M;
        cin >> M;
        ull sum = 0;
        for (int a = 3; a <= M; a++) {
            sum += brute_rmax(a);
        }
        cout << sum << "\n";
    }
    return 0;
}
