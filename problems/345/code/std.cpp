#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Hungarian algorithm for maximum assignment (max sum, one per row and column)
// Input: N×N matrix (positive values preferred)
// We negate values and run min-cost Hungarian, then negate answer.
// O(N^3)

const int MAXN = 20;
const ll INF = 1e18;

ll a[MAXN][MAXN];
ll u[MAXN], v[MAXN];
int p[MAXN], way[MAXN];

ll hungarian(int n) {
    memset(u, 0, sizeof(u));
    memset(v, 0, sizeof(v));
    memset(p, 0, sizeof(p));
    memset(way, 0, sizeof(way));
    
    for (int i = 1; i <= n; i++) {
        p[0] = i;
        int j0 = 0;
        vector<ll> minv(n + 1, INF);
        vector<int> used(n + 1, 0);
        do {
            used[j0] = 1;
            int i0 = p[j0];
            ll delta = INF;
            int j1 = 0;
            for (int j = 1; j <= n; j++) {
                if (!used[j]) {
                    ll cur = a[i0][j] - u[i0] - v[j];
                    if (cur < minv[j]) {
                        minv[j] = cur;
                        way[j] = j0;
                    }
                    if (minv[j] < delta) {
                        delta = minv[j];
                        j1 = j;
                    }
                }
            }
            for (int j = 0; j <= n; j++) {
                if (used[j]) {
                    u[p[j]] += delta;
                    v[j] -= delta;
                } else {
                    minv[j] -= delta;
                }
            }
            j0 = j1;
        } while (p[j0] != 0);
        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }
    
    // p[j] = row assigned to column j (1-indexed)
    // Answer: sum of assigned values (original, not negated)
    ll ans = 0;
    for (int j = 1; j <= n; j++) {
        ans += a[p[j]][j];
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
            a[i][j] = -a[i][j]; // convert to min-cost
        }
    }
    
    ll ans = -hungarian(n);
    cout << ans << "\n";
    return 0;
}
