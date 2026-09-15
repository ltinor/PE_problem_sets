#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M;
    cin >> M;
    ull sum = 0;
    for (int a = 3; a <= M; a++) {
        ull rmax = 2ULL * a * ((a - 1) / 2);
        sum += rmax;
    }
    cout << sum << "\n";
    return 0;
}
