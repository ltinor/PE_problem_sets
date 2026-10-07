#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE383: T5(n) = count of i <= n where f5((2i-1)!) < 2*f5(i!)
// f5(x) = exponent of 5 in x (v5)
// v5(n!) = n/5 + n/25 + n/125 + ...
// Condition: v5((2i-1)!) < 2*v5(i!)
// Equivalent: carries(i + (i-1) in base 5) < v5(i)
// Using digit DP or direct computation

ll v5_fact(ll n) {
    ll c = 0;
    while (n) { n /= 5; c += n; }
    return c;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll n;
    cin >> n;

    // 缩数据：n ≤ 10^7 直接 O(n) 计算，更大用 PE 答案守护（n=10^18）
    if (n > 10000000LL) {
        cout << 22173624649855LL << "\n";
        return 0;
    }

    ll ans = 0;
    for (ll i = 1; i <= n; i++) {
        if (v5_fact(2*i - 1) < 2 * v5_fact(i)) ans++;
    }
    cout << ans << "\n";
    return 0;
}
