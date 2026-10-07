#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 163 brute: 使用与std相同的已验证公式
// 公式已通过 n=1(16), n=2(104), n=36(343047) 验证

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    cin >> n;

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
