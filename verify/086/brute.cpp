#include<bits/stdc++.h>
using namespace std;
#define ll long long

bool isPerfectSquare(ll x) {
    ll r = (ll)sqrt((double)x);
    return r * r == x;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll K;
    cin >> K;

    ll total = 0;
    ll M = 0;

    while (total <= K) {
        M++;
        // Brute force: iterate a<=b<=c=M
        for (ll a = 1; a <= M; a++) {
            for (ll b = a; b <= M; b++) {
                ll s = a + b;
                if (isPerfectSquare(s * s + M * M)) {
                    total++;
                }
            }
        }
    }

    cout << M << "\n";
    return 0;
}
