#include<bits/stdc++.h>
using namespace std;

#define ll long long

bool is_prime(int n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

int A(int p) {
    if (p % 2 == 0 || p % 5 == 0) return 0;
    int r = 1 % p;
    int k = 1;
    while (r != 0) {
        r = (r * 10 + 1) % p;
        k++;
    }
    return k;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M;
    cin >> M;

    ll sum = 0;
    for (int p = 2; p < M; p++) {
        if (!is_prime(p)) continue;

        int a = A(p);
        if (a == 0) {
            sum += p;
            continue;
        }
        int temp = a;
        while (temp % 2 == 0) temp /= 2;
        while (temp % 5 == 0) temp /= 5;

        if (temp != 1) {
            sum += p;
        }
    }

    cout << sum << "\n";
    return 0;
}
