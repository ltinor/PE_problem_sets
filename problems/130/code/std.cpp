#include<bits/stdc++.h>
using namespace std;

int mygcd(int a, int b) { while(b){int t=b; b=a%b; a=t;} return a; }

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

int A(int n) {
    int r = 1 % n;
    int k = 1;
    while (r != 0) {
        r = (r * 10 + 1) % n;
        k++;
    }
    return k;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    cin >> K;

    vector<int> composites;
    for (int n = 3; ; n += 2) {
        if (n % 5 == 0) continue;
        if (mygcd(n, 10) != 1) continue;
        if (is_prime(n)) continue;  // skip primes

        int a = A(n);
        if ((n - 1) % a == 0) {
            composites.push_back(n);
            if ((int)composites.size() == K) break;
        }
    }

    ll sum = 0;
    for (int x : composites) sum += x;
    cout << sum << "\n";

    return 0;
}
