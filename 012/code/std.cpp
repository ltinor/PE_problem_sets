#include<bits/stdc++.h>
using namespace std;
#define ll long long

// 计算约数个数
int countDivisors(ll n) {
    int count = 0;
    for (ll i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            count++;
            if (i * i != n) count++;
        }
    }
    return count;
}

// 计算三角形数的约数个数
// T_n = n(n+1)/2
// 由于 n 和 n+1 互质，可以使用约数个数定理
int countTriangleDivisors(ll n) {
    if (n % 2 == 0) {
        // n 是偶数：T_n = (n/2) * (n+1)
        return countDivisors(n/2) * countDivisors(n+1);
    } else {
        // n 是奇数：T_n = n * ((n+1)/2)
        return countDivisors(n) * countDivisors((n+1)/2);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    cin >> K;

    for (ll n = 1; ; n++) {
        if (countTriangleDivisors(n) > K) {
            cout << n * (n + 1) / 2 << endl;
            break;
        }
    }
    return 0;
}
