#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 208: Robot Walks
// Robot takes n arcs of 72° (CW or CCW). Count closed paths returning to origin.
// Chord direction counts must all equal n/5 for return to origin.
// DP over (step, facing, chord_counts)
// Using combinatorial formula with BEST theorem:
// For given net circulation D = c - a: a = (n/5-D)/2, c = (n/5+D)/2
// Number of Eulerian circuits = t(D) * ((n/5-1)!)^5
// t(D) = (1/5) * |λ1|^2 * |λ2|^2
// λ1 = n/5 * (1-cos72°) - i*D*sin72°
// λ2 = n/5 * (1-cos144°) - i*D*sin144°
// Total paths = sum over valid D of EC(D)

// For n ≤ 200 (multiple of 5), compute directly

void print_i128(__int128 x) {
    if (x == 0) { cout << "0"; return; }
    string s;
    bool neg = false;
    if (x < 0) { neg = true; x = -x; }
    while (x) { s += char('0' + (int)(x % 10)); x /= 10; }
    if (neg) s += '-';
    reverse(s.begin(), s.end());
    cout << s;
}

// DP with hash map: track chord count differences
// Since all chord counts must = n/5, track 4 independent differences

struct State {
    int facing;
    int d[4]; // chord count differences from target
    
    bool operator==(const State& o) const {
        if (facing != o.facing) return false;
        for (int i = 0; i < 4; i++) if (d[i] != o.d[i]) return false;
        return true;
    }
};

struct StateHash {
    size_t operator()(const State& s) const {
        size_t h = s.facing;
        for (int i = 0; i < 4; i++) {
            h = h * 1000003 + (s.d[i] + 100);
        }
        return h;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    if (n % 5 != 0) {
        cout << "0\n";
        return 0;
    }

    // DP: state is (facing, c0, c1, c2, c3) where c4 = step - sum(ci)
    // Target at step n: c0=c1=c2=c3=c4=n/5
    int target = n / 5;

    unordered_map<State, __int128, StateHash> dp;
    State init;
    init.facing = 0;
    memset(init.d, 0, sizeof(init.d));
    dp[init] = 1;

    // Chord mapping:
    // CW from f: chord (f+4)%5, new facing (f+4)%5
    // CCW from f: chord f, new facing (f+1)%5

    for (int step = 0; step < n; step++) {
        unordered_map<State, __int128, StateHash> ndp;
        for (auto& [st, cnt] : dp) {
            int f = st.facing;
            // c4 = step - (st.d[0]+st.d[1]+st.d[2]+st.d[3])... 
            // Actually, track absolute chord counts, not differences
            // Let me redesign. Track actual c0,c1,c2,c3. c4 = step-sum.

            // Actually, the state already has d[0..3] which are the actual 
            // chord counts for directions 0-3. c4 = step - sum(d[0..3])
            int sum_d = st.d[0]+st.d[1]+st.d[2]+st.d[3];
            int c4 = step - sum_d;

            // CW from facing f: chord (f+4)%5, new facing (f+4)%5
            {
                int chord = (f + 4) % 5;
                State ns = st;
                if (chord < 4) ns.d[chord]++;
                // if chord==4, c4++ (implicit)
                ns.facing = (f + 4) % 5;
                ndp[ns] = ndp[ns] + cnt;
            }

            // CCW from facing f: chord f, new facing (f+1)%5
            {
                int chord = f;
                State ns = st;
                if (chord < 4) ns.d[chord]++;
                ns.facing = (f + 1) % 5;
                ndp[ns] = ndp[ns] + cnt;
            }
        }
        dp = move(ndp);
    }

    // Sum over states where all chord counts = target
    __int128 ans = 0;
    for (auto& [st, cnt] : dp) {
        if (st.d[0] == target && st.d[1] == target && 
            st.d[2] == target && st.d[3] == target) {
            // c4 = n - sum(d[0..3]) = n - 4*target = target. ✓
            ans += cnt;
        }
    }

    print_i128(ans);
    cout << "\n";
    return 0;
}
