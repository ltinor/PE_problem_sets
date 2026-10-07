#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Brute force: compute rad(n) via prime factorization
int rad_brute(int n) {
    int r = 1;
    int x = n;
    for (int p = 2; p * p <= x; p++) {
        if (x % p == 0) {
            r *= p;
            while (x % p == 0) x /= p;
        }
    }
    if (x > 1) r *= x;
    return r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N, K;
        cin >> N >> K;

        vector<pair<int, int>> v;
        for (int n = 1; n <= N; n++) {
            v.push_back({rad_brute(n), n});
        }
        sort(v.begin(), v.end());

        cout << v[K - 1].second << "\n";
    }
    return 0;
}
