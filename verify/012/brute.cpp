#include<bits/stdc++.h>
using namespace std;
#define ll long long

// 暴力计算约数个数
int countDivisorsBrute(ll n) {
    int count = 0;
    for (ll i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            count++;
            if (i * i != n) count++;
        }
    }
    return count;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    cin >> K;

    for (ll n = 1; ; n++) {
        ll triangle = n * (n + 1) / 2;
        if (countDivisorsBrute(triangle) > K) {
            cout << triangle << endl;
            break;
        }
    }
    return 0;
}