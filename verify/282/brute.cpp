#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Brute force Ackermann for very small values
ll ack(ll m, ll n) {
    if (m == 0) return n + 1;
    if (n == 0) return ack(m - 1, 1);
    return ack(m - 1, ack(m, n - 1));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int m;
    ll n, M;
    cin >> m >> n >> M;
    
    // Only brute for very small values
    if (m <= 2 || (m == 3 && n <= 10)) {
        ll val = ack(m, n);
        cout << val % M << "\n";
    } else {
        cout << "0\n"; // Can't brute force
    }
}
