#include <bits/stdc++.h>
using namespace std;

int main() {
    long long n;
    cin >> n;

    long long sum = 0;
    long long a = 1, b = 2;

    while (a <= n) {
        if (a % 2 == 0) sum += a;
        long long c = a + b;
        a = b;
        b = c;
    }

    cout << sum << endl;
    return 0;
}