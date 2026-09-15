#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    cin.ignore();

    int ans = 0;
    for (int i = 0; i < N; i++) {
        string w;
        getline(cin, w);

        int s = 0;
        for (char c : w) s += (c - 'A' + 1);

        // Check if s is triangle: t_n = n(n+1)/2
        // n^2 + n - 2s = 0 => n = floor(sqrt(2s))
        int n = (int)sqrt(2.0 * s);
        if (n * (n + 1) / 2 == s) ans++;
    }

    cout << ans << "\n";
    return 0;
}
