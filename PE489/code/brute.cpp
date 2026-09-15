#include<bits/stdc++.h>
using namespace std;
using ll = long long;

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll seq_a(ll n) { return n * n * n + n; }
ll seq_b(ll n) { return n * n + 1; }

int main() {
    ll N; cin >> N;
    ll total = 0;
    for (ll i = 1; i <= N; i++) {
        for (ll j = 1; j <= N; j++) {
            total += gcd(seq_a(i), seq_b(j));
        }
    }
    cout << total << "\n";
}
