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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    if (N <= 0 || N > 9) { cout << "-1\n"; return 0; }
    // Sum 1..N: if divisible by 3, no pandigital can be prime
    if (N == 8 || N == 9 || N == 1) { cout << "-1\n"; return 0; }
    string s;
    for (int i = N; i >= 1; i--) s += char('0' + i);
    do {
        int x = stoi(s);
        if (is_prime(x)) { cout << x << "\n"; return 0; }
    } while (prev_permutation(s.begin(), s.end()));
    cout << "-1\n";
}
