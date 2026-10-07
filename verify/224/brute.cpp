#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Brute force: triple loop a <= b <= c
// a^2 + b^2 = c^2 - 1, a+b+c <= N

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    ll ans = 0;
    for(ll a = 1; 3*a <= N; a++) {
        for(ll b = a; a + 2*b <= N; b++) {
            // c^2 = a^2 + b^2 + 1
            ll c2 = a*a + b*b + 1;
            ll c = (ll)sqrt(c2);
            if(c >= b && c*c == c2 && a + b + c <= N) {
                ans++;
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
