#include <bits/stdc++.h>
using namespace std;

bool is_prime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N; cin >> N;
    if (N >= 8) { cout << "-1\n"; return 0; }
    vector<int> v(N);
    for (int i = 0; i < N; i++) v[i] = N - i;
    do {
        int x = 0;
        for (int d : v) x = x * 10 + d;
        if (is_prime(x)) { cout << x << "\n"; return 0; }
    } while (prev_permutation(v.begin(), v.end()));
    cout << "-1\n";
}
