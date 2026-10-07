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

    int K, N;
    cin >> K >> N;

    vector<ll> factors;
    for (int p = 7; ; p += 2) {
        if (p % 5 == 0) continue;
        if (!is_prime(p)) continue;

        int a = A(p);
        int temp = a;
        int cnt2 = 0, cnt5 = 0;
        while (temp % 2 == 0) { temp /= 2; cnt2++; }
        while (temp % 5 == 0) { temp /= 5; cnt5++; }

        if (temp == 1 && cnt2 <= N && cnt5 <= N) {
            factors.push_back(p);
            if ((int)factors.size() == K) break;
        }
    }

    ll sum = 0;
    for (ll x : factors) sum += x;
    cout << sum << "\n";

    return 0;
}
