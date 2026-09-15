#include<bits/stdc++.h>
using namespace std;
using ll = long long;

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

// Brute force: enumerate all permutations of n
ll brute_perm(int n) {
    vector<int> p(n);
    iota(p.begin(), p.end(), 0);
    ll total = 0;
    do {
        // Compute LCM of cycle lengths for this permutation
        vector<bool> vis(n, false);
        ll l = 1;
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                int len = 0, j = i;
                while (!vis[j]) {
                    vis[j] = true;
                    j = p[j];
                    len++;
                }
                l = l / gcd(l, (ll)len) * len;
            }
        }
        total += l;
    } while (next_permutation(p.begin(), p.end()));
    return total;
}

int main() {
    int n; cin >> n;
    cout << brute_perm(n) << "\n";
}
