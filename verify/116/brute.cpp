#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

ull count_ways(int n, int L) {
    vector<ull> f(n + 1, 0);
    f[0] = 1;
    for (int i = 1; i <= n; i++) {
        f[i] = f[i - 1];
        if (i >= L) f[i] += f[i - L];
    }
    return f[n] - 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        ull ans = count_ways(N, 2) + count_ways(N, 3) + count_ways(N, 4);
        cout << ans << "\n";
    }
    return 0;
}
