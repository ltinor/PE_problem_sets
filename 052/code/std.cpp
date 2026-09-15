#include<bits/stdc++.h>
using namespace std;
#define ll long long

bool is_permutation(ll a, ll b) {
    string sa = to_string(a);
    string sb = to_string(b);
    sort(sa.begin(), sa.end());
    sort(sb.begin(), sb.end());
    return sa == sb;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M;
    cin >> M;

    for (ll x = 1; ; x++) {
        bool ok = true;
        for (int k = 2; k <= M; k++) {
            if (!is_permutation(x, k * x)) {
                ok = false;
                break;
            }
        }
        if (ok) {
            cout << x << "\n";
            return 0;
        }
    }
    return 0;
}
