#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Minkowski sum of regular n-gons S_L + ... + S_R
// S_n has vertices at (cos((2k-1)*PI/n), sin((2k-1)*PI/n))
// Edge outward normals are at angles 2*PI*k/n, k=1..n
// These correspond to fractions k/n in lowest terms
// Distinct reduced fractions across all n in [L,R] give the sides count

int mygcd(int a, int b) {
    while (b) { int t = b; b = a % b; a = t; }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int L, R;
    cin >> L >> R;

    set<pair<int,int>> fracs;

    for (int n = L; n <= R; n++) {
        for (int k = 1; k <= n; k++) {
            int g = mygcd(k, n);
            fracs.insert({k / g, n / g});
        }
    }

    cout << fracs.size() << "\n";
    return 0;
}
