#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 237: Tours on a 4×n playing board
// Uses profile DP with states encoded as connectivity patterns
// on the boundary between processed and unprocessed cells.
// Reference: known transfer matrix for 4×n Hamiltonian path from top-left to bottom-left.

const int MOD = 100000000;

typedef vector<vector<ll>> Matrix;

Matrix mul(const Matrix& A, const Matrix& B) {
    int n = A.size();
    Matrix C(n, vector<ll>(n, 0));
    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++)
            if (A[i][k])
                for (int j = 0; j < n; j++)
                    C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
    return C;
}

Matrix power(Matrix A, ll e) {
    int n = A.size();
    Matrix R(n, vector<ll>(n, 0));
    for (int i = 0; i < n; i++) R[i][i] = 1;
    while (e) {
        if (e & 1) R = mul(R, A);
        A = mul(A, A);
        e >>= 1;
    }
    return R;
}

// State: connectivity of 4 cells on the column boundary
// Using integer partition encoding: each cell has a label 0..3
// Same label = connected through processed columns
// Labels are normalized: first unused label assigned to next unlabeled plug

// We only need states with 0 or 2 plugs (since start/end create a path
// that enters at 2 rows and exits at 2 rows, or 0 at the end)

// State encoding: 4-digit base-4 number for compactness
// Maximum label is 2 (since at most 2 independent connections)

int encode_state(const vector<int>& v) {
    int h = 0;
    for (int i = 3; i >= 0; i--) h = h * 4 + v[i];
    return h;
}

void decode_state(int h, vector<int>& v) {
    v.resize(4);
    for (int i = 0; i < 4; i++) { v[i] = h % 4; h /= 4; }
}

// Normalize: map labels to 0,1,2 compactly
int normalize(vector<int>& v) {
    int remap[4] = {-1, -1, -1, -1};
    int next = 0;
    for (int& x : v) {
        if (x == 0) continue;
        if (remap[x] == -1) remap[x] = ++next;
        x = remap[x];
    }
    return next;
}

// Generate all valid states (0 or 2 or 4 plugs, properly paired)
vector<int> generate_states() {
    vector<int> states;
    // Enumerate all base-4 patterns with each label appearing 0 or 2 times
    for (int h = 0; h < 256; h++) {
        vector<int> v;
        decode_state(h, v);
        int cnt[4] = {0,0,0,0};
        for (int x : v) if (x < 4) cnt[x]++;
        bool ok = true;
        for (int x = 1; x <= 3; x++)
            if (cnt[x] != 0 && cnt[x] != 2) { ok = false; break; }
        if (ok) {
            // Normalize
            vector<int> w = v;
            normalize(w);
            int nh = encode_state(w);
            states.push_back(nh);
        }
    }
    // Unique
    sort(states.begin(), states.end());
    states.erase(unique(states.begin(), states.end()), states.end());
    return states;
}

// For each state, generate all possible next states by filling one column
// Column filling: connect left plugs, add vertical edges, create right plugs
// All 4 cells must be visited exactly once (degree 2 each for interior columns)

void generate_transitions(const vector<int>& states,
                          Matrix& T, int start_idx, int end_idx) {
    int S = states.size();
    map<int,int> idx;
    for (int i = 0; i < S; i++) idx[states[i]] = i;

    for (int si = 0; si < S; si++) {
        vector<int> left;
        decode_state(states[si], left);

        // Enumerate all column fillings
        // A column filling specifies:
        // - Which vertical edges exist (0,1), (1,2), (2,3) -> 8 possibilities
        // - For each cell, whether it connects to the right -> 16 possibilities

        for (int vert = 0; vert < 8; vert++) {
            bool e01 = vert & 1, e12 = vert & 2, e23 = vert & 4;

            for (int rmask = 0; rmask < 16; rmask++) {
                // Compute degree of each cell
                int deg[4] = {};
                for (int r = 0; r < 4; r++)
                    if (left[r] > 0) deg[r]++;
                if (e01) deg[0]++, deg[1]++;
                if (e12) deg[1]++, deg[2]++;
                if (e23) deg[2]++, deg[3]++;
                for (int r = 0; r < 4; r++)
                    if (rmask & (1 << r)) deg[r]++;

                // For interior columns: all cells must have degree 2
                bool ok = true;
                for (int r = 0; r < 4; r++)
                    if (deg[r] != 2) { ok = false; break; }
                if (!ok) continue;

                // Check connectivity: the subgraph within this column
                // (via vertical edges) should not have connected components
                // with no left/right plugs (that would form isolated cycles)

                // Build graph of cells connected by vertical edges
                vector<int> adj[4];
                if (e01) adj[0].push_back(1), adj[1].push_back(0);
                if (e12) adj[1].push_back(2), adj[2].push_back(1);
                if (e23) adj[2].push_back(3), adj[3].push_back(2);

                // Find connected components
                int comp[4] = {-1, -1, -1, -1};
                int comp_cnt = 0;
                for (int r = 0; r < 4; r++) {
                    if (comp[r] == -1) {
                        queue<int> q;
                        q.push(r);
                        comp[r] = comp_cnt;
                        while (!q.empty()) {
                            int u = q.front(); q.pop();
                            for (int v : adj[u])
                                if (comp[v] == -1) {
                                    comp[v] = comp[u];
                                    q.push(v);
                                }
                        }
                        comp_cnt++;
                    }
                }

                // Each component must have at least one left or right plug
                bool comp_ok = true;
                for (int c = 0; c < comp_cnt; c++) {
                    bool has_plug = false;
                    for (int r = 0; r < 4; r++) {
                        if (comp[r] == c && (left[r] > 0 || (rmask & (1 << r))))
                            has_plug = true;
                    }
                    if (!has_plug) { comp_ok = false; break; }
                }
                if (!comp_ok) continue;

                // Determine right plugs connectivity
                // Each right plug inherits connectivity from its component
                // Left plugs in the same component connect through the column
                // to right plugs in that component

                vector<int> right(4, 0);

                // For each component, find the label(s) from left plugs
                // and assign to right plugs
                map<int, int> comp_left_label; // component -> label
                for (int r = 0; r < 4; r++) {
                    if (left[r] > 0) {
                        comp_left_label[comp[r]] = left[r];
                    }
                }

                // Count right plugs per component
                vector<int> comp_right_cnt(comp_cnt, 0);
                vector<int> comp_right_rows[4];
                for (int r = 0; r < 4; r++) {
                    if (rmask & (1 << r)) {
                        comp_right_cnt[comp[r]]++;
                        comp_right_rows[comp[r]].push_back(r);
                    }
                }

                // For each component:
                // - If it has a left plug and exactly 1 right plug: right gets same label
                // - If it has a left plug and 2 right plugs: right gets same label (paired through right side)
                // - If it has no left plug and 2 right plugs: create new label
                // - If it has 0 left plugs and 0 right plugs: impossible (already filtered)
                // - If it has 0 left plugs and 1 right plug: impossible (deg constraint already filtered)
                // - If it has a left plug and 0 right plugs: label disappears (right stays 0)

                bool trans_ok = true;
                for (int c = 0; c < comp_cnt; c++) {
                    int lp = comp_left_label.count(c) ? comp_left_label[c] : 0;
                    int rp = comp_right_cnt[c];

                    if (lp == 0 && rp == 0) continue; // empty component? shouldn't happen
                    if (lp == 0 && rp == 2) {
                        // New connection: assign fresh label
                        // Will be normalized later
                        static int fresh = 10;
                        for (int r : comp_right_rows[c])
                            right[r] = fresh;
                        fresh++;
                    } else if (lp > 0 && rp == 1) {
                        // Single right plug inherits left label
                        right[comp_right_rows[c][0]] = lp;
                    } else if (lp > 0 && rp == 2) {
                        // Two right plugs: both get same label (connected through right)
                        for (int r : comp_right_rows[c])
                            right[r] = lp;
                    } else if (lp > 0 && rp == 0) {
                        // Label disappears (connection resolved within column)
                        // OK, nothing to do
                    } else {
                        trans_ok = false; // invalid count
                    }
                }
                if (!trans_ok) continue;

                // Normalize right state labels
                normalize(right);
                int right_code = encode_state(right);

                if (idx.count(right_code)) {
                    T[si][idx[right_code]]++;
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    cin >> n;

    if (n == 1) { cout << "1\n"; return 0; }

    auto states = generate_states();
    int S = states.size();
    map<int,int> idx;
    for (int i = 0; i < S; i++) idx[states[i]] = i;

    Matrix T(S, vector<ll>(S, 0));
    generate_transitions(states, T, -1, -1);

    // Initial state: column 0 with start at top-left, end at bottom-left
    // After column 0, there's exactly 2 right plugs (path exits to column 1)
    // The two plugs are connected through the right side (same label)

    // Enumerate initial configurations for column 0
    // Column 0 has start at (0,0) and end at (3,0)
    // Path goes through all 4 cells, some have right connections

    vector<ll> init(S, 0);
    int empty_idx = idx[0];

    // Enumerate column 0 fillings
    for (int vert = 0; vert < 8; vert++) {
        bool e01 = vert & 1, e12 = vert & 2, e23 = vert & 4;
        for (int rmask = 0; rmask < 16; rmask++) {
            int bits = __builtin_popcount(rmask);
            if (bits != 2) continue;

            int deg[4] = {};
            deg[0]++; // start
            deg[3]++; // end
            if (e01) deg[0]++, deg[1]++;
            if (e12) deg[1]++, deg[2]++;
            if (e23) deg[2]++, deg[3]++;
            for (int r = 0; r < 4; r++)
                if (rmask & (1 << r)) deg[r]++;

            bool ok = true;
            for (int r = 0; r < 4; r++)
                if (deg[r] != 2) { ok = false; break; }
            if (!ok) continue;

            // Check column 0 internal connectivity (must be one path from 0 to 3)
            vector<int> comp(4, -1);
            int comps = 0;
            for (int r = 0; r < 4; r++) {
                if (comp[r] == -1) {
                    queue<int> q; q.push(r); comp[r] = comps;
                    while (!q.empty()) {
                        int u = q.front(); q.pop();
                        if (u > 0 && e01 && comp[u-1] == -1) {
                            if ((u == 1 && u-1 == 0) || (u-1 == 1 && u == 0)) {}
                            // Actually just check vertical neighbors
                        }
                        // Neighbors via vertical edges
                        if (u == 0 && e01 && comp[1] == -1) { comp[1] = comps; q.push(1); }
                        if (u == 1) {
                            if (e01 && comp[0] == -1) { comp[0] = comps; q.push(0); }
                            if (e12 && comp[2] == -1) { comp[2] = comps; q.push(2); }
                        }
                        if (u == 2) {
                            if (e12 && comp[1] == -1) { comp[1] = comps; q.push(1); }
                            if (e23 && comp[3] == -1) { comp[3] = comps; q.push(3); }
                        }
                        if (u == 3 && e23 && comp[2] == -1) { comp[2] = comps; q.push(2); }
                    }
                    comps++;
                }
            }

            // Must be connected (one component)
            if (comps != 1) continue;

            // Right plugs get both label 1
            vector<int> right(4, 0);
            for (int r = 0; r < 4; r++)
                if (rmask & (1 << r)) right[r] = 1;

            int rc = encode_state(right);
            if (idx.count(rc))
                init[idx[rc]]++;
        }
    }

    // Apply T^{n-1}
    Matrix Tn = power(T, n - 1);

    ll ans = 0;
    for (int i = 0; i < S; i++)
        ans = (ans + init[i] * Tn[i][empty_idx]) % MOD;

    cout << ans << "\n";
    return 0;
}
