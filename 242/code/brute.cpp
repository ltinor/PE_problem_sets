#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Efficient brute using the condition directly
// For n odd, triplets: odd k where f(n,k) is odd
// f(n,k) = sum_{odd o} C(O,o)C(E,k-o), O=(n+1)/2, E=n/2
// Lucas: C(a,b) is odd iff b ⊆ a
// So f(n,k) odd iff # of odd o with o⊆O and k-o⊆E is odd

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll N;
    cin >> N;
    
    ll ans = 0;
    
    for (ll n = 1; n <= N; n += 2) {
        ll O = (n + 1) / 2;
        ll E = n / 2;
        
        ll cnt = 0;
        for (ll k = 1; k <= n; k += 2) {
            bool f_odd = false;
            for (ll o = 1; o <= O && o <= k; o += 2) {
                ll e = k - o;
                if (e > E) continue;
                if ((o & ~O) == 0 && (e & ~E) == 0) {
                    f_odd = !f_odd;
                }
            }
            if (f_odd) cnt++;
        }
        ans += cnt;
    }
    
    cout << ans << "\n";
    return 0;
}
