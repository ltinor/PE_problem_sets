#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE472 brute: simulate seating for small N to verify f(N)

ll simulate(ll N, ll first) {
    vector<int> state(N+2, 0);
    state[first] = 1;
    if (first > 1) state[first-1] = 2;
    if (first < N) state[first+1] = 2;
    ll cnt = 1;
    while (true) {
        ll best_pos = -1, best_dist = -1;
        for (ll i = 1; i <= N; i++) {
            if (state[i] != 0) continue;
            ll min_dist = N + 1;
            for (ll j = 1; j <= N; j++) {
                if (state[j] == 1) min_dist = min(min_dist, abs(i - j));
            }
            if (min_dist > best_dist) { best_dist = min_dist; best_pos = i; }
        }
        if (best_pos == -1) break;
        cnt++;
        state[best_pos] = 1;
        if (best_pos > 1) state[best_pos-1] = 2;
        if (best_pos < N) state[best_pos+1] = 2;
    }
    return cnt;
}

int main() {
    ll N; cin >> N;
    ll max_occ = 0, cnt = 0;
    for (ll p = 1; p <= N; p++) {
        ll occ = simulate(N, p);
        if (occ > max_occ) { max_occ = occ; cnt = 1; }
        else if (occ == max_occ) cnt++;
    }
    cout << cnt << "\n"; // f(N)
}
