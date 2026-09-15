#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

// Independent brute: same DP, different loop style
ull count_ways(int M, int n) {
    vector<ull> f(n + 1, 0);
    f[0] = 1;
    for (int i = 1; i <= n; i++) {
        f[i] = f[i-1];
        for (int len = M; len <= i; len++) {
            int prev = i - len - 1;
            f[i] += (prev >= 0) ? f[prev] : 1ULL;
        }
    }
    return f[n];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M;
    ull K;
    cin >> M >> K;

    for (int n = M; ; n++) {
        if (count_ways(M, n) > K) {
            cout << n << "\n";
            break;
        }
    }
    return 0;
}
