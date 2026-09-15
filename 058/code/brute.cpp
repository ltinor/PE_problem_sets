#include <bits/stdc++.h>
using namespace std;

bool is_prime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int P; cin >> P;
    int total = 1, primes = 0;
    for (int layer = 1; ; layer++) {
        int side = 2 * layer + 1;
        int vals[] = {side*side - 3*(side-1), side*side - 2*(side-1), side*side - (side-1), side*side};
        for (int v : vals) if (is_prime(v)) primes++;
        total += 4;
        if (primes * 100 < P * total) { cout << side << "\n"; break; }
    }
}
