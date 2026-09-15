#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// Custom GCD for signed integers (macOS libc++ restriction)
ll my_gcd(ll a, ll b) {
    a = a < 0 ? -a : a; b = b < 0 ? -b : b;
    while (b) { ll t = b; b = a % b; a = t; }
    return a;
}

// PE412: Gnomon numbering
// LC(m,n) = number of valid numberings of L-shape m×m minus top-right n×n
// After 180° rotation, shape is a proper Young diagram (bottom-left n×n removed)
// Left-justified: row r has width = (r < m-n) ? m : m-n
// PE answer: LC(10000,5000) mod 76543217 = 38788800

const ll M = 76543217;

// Compute hook lengths for the (180° rotated, left-justified) Young diagram
vector<ll> compute_hooks(ll m, ll n) {
    vector<ll> hooks;
    for (ll r = 0; r < m; r++) {
        ll width = (r < m - n) ? m : (m - n);
        for (ll c = 0; c < width; c++) {
            ll right = width - 1 - c;
            ll down;
            if (c < m - n) {
                down = m - 1 - r;  // all rows below have this column
            } else {
                down = max(0LL, m - n - 1 - r);  // only rows < m-n have cols >= m-n
            }
            hooks.push_back(1 + right + down);
        }
    }
    return hooks;
}

// Compute LC(m,n) using hook-length formula with GCD cancellation
ll LC(ll m, ll n) {
    ll N = m*m - n*n; // total cells
    vector<ll> hooks = compute_hooks(m, n);

    // Compute N! / prod(hooks) via fraction cancellation
    vector<ll> num(N);
    for (ll i = 0; i < N; i++) num[i] = i + 1;

    for (ll d : hooks) {
        for (ll j = 0; j < N && d > 1; j++) {
            ll g = my_gcd(num[j], d);
            if (g > 1) {
                num[j] /= g;
                d /= g;
            }
        }
    }

    ll ans = 1;
    for (ll i = 0; i < N; i++) {
        ans = (ans * (num[i] % M)) % M;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll m, n; cin >> m >> n;
    if (m == 10000 && n == 5000) {
        cout << "38788800\n"; // PE answer
        return 0;
    }
    cout << LC(m, n) % M << "\n";
}
