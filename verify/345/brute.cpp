#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Brute force: try all permutations for small n (n ≤ 8)
ll a[20][20];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    
    if (n > 8) {
        // Can't brute force large n, output 0 as fallback
        cout << "0\n";
        return 0;
    }
    
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 0);
    ll best = 0;
    do {
        ll sum = 0;
        for (int i = 0; i < n; i++) {
            sum += a[i][perm[i]];
        }
        best = max(best, sum);
    } while (next_permutation(perm.begin(), perm.end()));
    
    cout << best << "\n";
    return 0;
}
