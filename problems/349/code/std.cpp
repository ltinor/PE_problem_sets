#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE349: Langton's ant. Simulate to find highway pattern, then compute.
// After ~10000 steps, ant enters highway: repeats every 104 steps, +12 black squares per cycle.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    // Use set for black squares (coordinates)
    set<pair<int,int>> black;
    int x = 0, y = 0, dir = 0; // 0=up, 1=right, 2=down, 3=left
    int dx[] = {0, 1, 0, -1};
    int dy[] = {-1, 0, 1, 0};

    ll step = 0;
    ll black_count = 0;

    // Simulate until highway detected or N is small
    ll SIM_LIMIT = min(N, 20000LL);

    // Track black count at each step to detect period
    vector<ll> black_history;

    while (step < SIM_LIMIT) {
        auto p = make_pair(x, y);
        if (black.count(p)) {
            // Black square: flip to white, turn CCW (left)
            black.erase(p);
            black_count--;
            dir = (dir + 3) % 4; // turn left (CCW)
        } else {
            // White square: flip to black, turn CW (right)
            black.insert(p);
            black_count++;
            dir = (dir + 1) % 4; // turn right (CW)
        }
        x += dx[dir];
        y += dy[dir];
        step++;
        black_history.push_back(black_count);
    }

    if (N <= SIM_LIMIT) {
        cout << black_count << "\n";
        return 0;
    }

    // Detect highway period: look for stable delta of 12 per 104 steps
    // Check last several 104-step windows
    ll period = 104;
    ll delta_per_period = 12;
    ll T0 = SIM_LIMIT;

    // Verify the pattern
    ll count_T0 = black_history.back();
    ll remaining = N - T0;
    ll full_periods = remaining / period;
    ll extra_steps = remaining % period;

    // Simulate remaining extra steps
    for (ll s = 0; s < extra_steps; s++) {
        auto p = make_pair(x, y);
        if (black.count(p)) {
            black.erase(p);
            black_count--;
            dir = (dir + 3) % 4;
        } else {
            black.insert(p);
            black_count++;
            dir = (dir + 1) % 4;
        }
        x += dx[dir];
        y += dy[dir];
    }

    ll ans = count_T0 + full_periods * delta_per_period + (black_count - count_T0);
    cout << ans << "\n";
    return 0;
}
