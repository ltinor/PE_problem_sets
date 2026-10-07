#include<bits/stdc++.h>
using namespace std;

#define ll long long

// DFS brute force: generate all trinary strings and count valid ones
// Only works for small N (N <= 12)

int N;
ll ans = 0;

void dfs(int day, int late, int consec_absent) {
    if (day == N) {
        ans++;
        return;
    }

    // On time
    dfs(day + 1, late, 0);

    // Late
    if (late == 0) {
        dfs(day + 1, 1, 0);
    }

    // Absent
    if (consec_absent < 2) {
        dfs(day + 1, late, consec_absent + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;

    ans = 0;
    dfs(0, 0, 0);

    cout << ans << "\n";
    return 0;
}
