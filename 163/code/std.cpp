#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 163: 交错三角形计数 T(N)
// 使用闭式公式（已验证n=1,2）

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    cin >> n;

    // T(n) = (1678*n³ + 3117*n² + 88*n - C(n)) / 240
    // C(n) = 345*(n%2) + 320*(n%3) + 90*(n%4) + 288*((n³-n²+n)%5)

    ll n3 = n * n * n;
    ll n2 = n * n;

    ll num = 1678 * n3 + 3117 * n2 + 88 * n;

    ll c1 = 345 * (n % 2);
    ll c2 = 320 * (n % 3);
    ll c3 = 90 * (n % 4);
    ll c4 = 288 * ((n3 - n2 + n) % 5);

    num -= (c1 + c2 + c3 + c4);

    ll ans = num / 240;
    cout << ans << "\n";
}
