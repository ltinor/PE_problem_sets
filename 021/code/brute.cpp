#include<bits/stdc++.h>
using namespace std;

int proper_divisor_sum(int n) {
    if (n <= 1) return 0;
    int sum = 1;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            sum += i;
            int j = n / i;
            if (j != i) sum += j;
        }
    }
    return sum;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;

        long long ans = 0;
        // For each a < N, compute d(a)=b.
        // If b > a and d(b)==a, then a is amicable (partner may be >= N).
        for (int a = 1; a < N; a++) {
            int b = proper_divisor_sum(a);
            if (b > a && proper_divisor_sum(b) == a) {
                ans += a;
                // If partner b is also < N, add it too
                if (b < N) ans += b;
            }
        }

        cout << ans << "\n";
    }

    return 0;
}
