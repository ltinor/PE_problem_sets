#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n;
    cin >> n;

    long long sum = 0;
    long long a = 2, b = 8;
    while (a <= n) {
        sum += a;
        long long c = 4 * b + a;
        a = b;
        b = c;
    }

    cout << sum << endl;
    return 0;
}