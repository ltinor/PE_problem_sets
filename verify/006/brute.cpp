#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        long long K;
        cin >> K;
        long long sum = 0, sum_sq = 0;
        for (long long i = 1; i <= K; i++) {
            sum += i;
            sum_sq += i*i;
        }
        cout << sum*sum - sum_sq << '\n';
    }
    return 0;
}