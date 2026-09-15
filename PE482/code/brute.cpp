#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// Brute force: enumerate all triangles with integer sides ≤ N
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

ll brute_incenter(ll N) {
    ll total = 0;
    for (ll a = 1; a <= N; a++) {
        for (ll b = a; b <= N; b++) {
            for (ll c = b; c <= N && c < a + b; c++) {
                if (a + b + c > N) break;
                // Triangle inequality satisfied since c < a+b
                // Incenter: barycentric (a:b:c)
                // Sum something simple for brute
                total += a + b + c; // placeholder
            }
        }
    }
    return total;
}

int main() {
    ll N; cin >> N;
    cout << brute_incenter(N) << "\n";
}
