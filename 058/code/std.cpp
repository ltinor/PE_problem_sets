#include <bits/stdc++.h>
using namespace std;

bool is_prime(int n) {
    if (n < 2) return false;
    if (n % 2 == 0) return n == 2;
    for (int i = 3; i * i <= n; i += 2)
        if (n % i == 0) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int P; cin >> P;
    int total = 1, primes = 0; // center = 1 (not prime)
    for (int layer = 1; ; layer++) {
        int side = 2 * layer + 1;
        int tr = side * side;                  // top-right
        int tl = tr - (side - 1);              // top-left
        int bl = tl - (side - 1);              // bottom-left
        int br = bl - (side - 1);              // bottom-right
        if (is_prime(tl)) primes++;
        if (is_prime(tr)) primes++;
        if (is_prime(bl)) primes++;
        if (is_prime(br)) primes++;
        total += 4;
        if (primes * 100 < P * total) { cout << side << "\n"; break; }
    }
}
