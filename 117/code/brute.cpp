#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<ull> f(N + 1, 0);
        f[0] = 1;
        for (int i = 1; i <= N; i++) {
            f[i] = f[i - 1];
            if (i >= 2) f[i] += f[i - 2];
            if (i >= 3) f[i] += f[i - 3];
            if (i >= 4) f[i] += f[i - 4];
        }
        cout << f[N] << "\n";
    }
    return 0;
}
