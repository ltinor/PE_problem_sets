#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// Brute force: compute divisor counts and sliding maximum
int divisor_count(int n) {
    int cnt = 0;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            cnt++;
            if (i * i != n) cnt++;
        }
    }
    return cnt;
}

int main() {
    int U, K; cin >> U >> K;
    vector<int> d(U + 1);
    for (int i = 1; i <= U; i++) d[i] = divisor_count(i);

    ll sum = 0;
    for (int i = 1; i + K - 1 <= U; i++) {
        int mx = 0;
        for (int j = i; j < i + K; j++) mx = max(mx, d[j]);
        sum += mx;
    }
    cout << sum << "\n";
}
