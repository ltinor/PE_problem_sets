#include <bits/stdc++.h>
using namespace std;
using ll = unsigned long long;

// PE 505（缩数据真算法版）：双向递推
//  x(0)=0, x(1)=1
//  x(2k)   = (3x(k) + 2x(floor(k/2))) mod 2^60   (k>=1)
//  x(2k+1) = (2x(k) + 3x(floor(k/2))) mod 2^60   (k>=1)
//  y_n(k) = x(k)  if k >= n
//  y_n(k) = 2^60 - 1 - max(y_n(2k), y_n(2k+1))  if k < n
//  A(n) = y_n(1)
// 缩数据：n <= 10^6。验证点：A(4)=8, A(10)=2^60-34, A(1000)=101881。

const ll MASK = ((ll)1 << 60) - 1; // 2^60 - 1

unordered_map<ll, ll> xmemo;

ll xval(ll k) {
    if (k == 0) return 0;
    if (k == 1) return 1;
    auto it = xmemo.find(k);
    if (it != xmemo.end()) return it->second;
    ll h = k / 2;
    ll r;
    if (k % 2 == 0) r = (3 * xval(h) + 2 * xval(h / 2)) & MASK;
    else            r = (2 * xval(h) + 3 * xval(h / 2)) & MASK;
    return xmemo[k] = r;
}

ll n_global;
unordered_map<ll, ll> ymemo;

ll yval(ll k) {
    if (k >= n_global) return xval(k);
    auto it = ymemo.find(k);
    if (it != ymemo.end()) return it->second;
    ll r = MASK - max(yval(2 * k), yval(2 * k + 1));
    return ymemo[k] = r;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll n;
    if (!(cin >> n)) return 0;
    if (n > 1000000) { cout << "n 超出缩数据范围（需 n<=10^6）\n"; return 0; }
    n_global = n;
    cout << yval(1) << "\n";
    return 0;
}
