#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n;
    cin >> n;
    long long ans = 0;

    for (long long i = 2; i * i <= n; ++i) {
        while (n % i == 0) {
            ans = i;
            n /= i;
        }
    }

    if (n > 1) ans = n;

    cout << ans << endl;
    return 0;
}