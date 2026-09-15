#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        long long K;
        cin >> K;
        long long sum = K * (K + 1) / 2;
        long long sum_sq = K * (K + 1) * (2*K + 1) / 6;
        cout << sum*sum - sum_sq << '\n';
    }
    return 0;
}