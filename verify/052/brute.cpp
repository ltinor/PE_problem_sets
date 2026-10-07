#include<bits/stdc++.h>
using namespace std;
#define ll long long

int cnt[10], cnt2[10];

bool is_permutation(ll a, ll b) {
    memset(cnt, 0, sizeof(cnt));
    memset(cnt2, 0, sizeof(cnt2));
    while (a) { cnt[a % 10]++; a /= 10; }
    while (b) { cnt2[b % 10]++; b /= 10; }
    for (int i = 0; i < 10; i++)
        if (cnt[i] != cnt2[i]) return false;
    return true;
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
