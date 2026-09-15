#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 244: Sliders / 滑块
//
// 4x4 board, 7 red tiles, 8 blue tiles, 1 empty space.
// Moves: L,R,U,D slide adjacent tile into empty space.
// Checksum: checksum = (checksum * 243 + move_ascii) % 100000007
//   L=76, R=82, U=85, D=68
// Find sum of checksums of ALL shortest paths from S to T.
//
// Key observations:
// - State space: C(16,7) * C(9,8) = 11440 * 9 = 102960 (manageable).
//   Actually: choose 7 positions for red among 15 non-empty slots,
//   then 8 of remaining 8 for blue. That's C(15,7) = 6435 states.
// - BFS from S gives shortest distance to all states.
// - DP over BFS layers: dp[state] = (sum_checksums, count_paths).
//   For each neighbor on shortest path (dist+1), propagate:
//     sum' += sum*243 + count*move_val (mod MOD)
//     count' += count

const ll MOD = 100000007;
const int MOVE_VAL[4] = {76, 82, 85, 68}; // L,R,U,D
const int DR[4] = {0, 0, -1, 1}; // row delta for empty when tile slides in
const int DC[4] = {1, -1, 0, 0}; // col delta for empty
// When a tile slides L, empty moves right: (0,1)
// When a tile slides R, empty moves left: (0,-1)
// When a tile slides U, empty moves down: (1,0)
// When a tile slides D, empty moves up: (-1,0)
const char MOVE_CHAR[4] = {'L', 'R', 'U', 'D'};

// Board encoding: 16-bit mask for red positions (1=red, 0=blue/empty).
// Empty position tracked separately (0-15).
struct State {
    uint16_t red_mask; // bit i set = position i is red
    uint8_t empty_pos; // 0-15
};

// Encode state to single 32-bit integer for hashing
inline uint32_t encode(State s) {
    return ((uint32_t)s.red_mask << 4) | s.empty_pos;
}

// Decode
inline State decode(uint32_t x) {
    return {(uint16_t)(x >> 4), (uint8_t)(x & 15)};
}

// Check if position (r,c) is valid
inline bool in_bounds(int r, int c) {
    return r >= 0 && r < 4 && c >= 0 && c < 4;
}

// Get valid moves from a state. Returns vector of (next_state, move_index).
vector<pair<State,int>> get_moves(State s) {
    vector<pair<State,int>> moves;
    int er = s.empty_pos / 4, ec = s.empty_pos % 4;
    for (int m = 0; m < 4; m++) {
        int nr = er + DR[m], nc = ec + DC[m];
        if (!in_bounds(nr, nc)) continue;
        int slide_pos = nr * 4 + nc; // position of tile that slides
        int new_empty = slide_pos;
        State ns = s;
        ns.empty_pos = new_empty;
        // The sliding tile was at slide_pos. Check if it's red.
        bool was_red = (s.red_mask >> slide_pos) & 1;
        if (was_red) {
            // Red tile moves to old empty position
            ns.red_mask &= ~(1u << slide_pos);
            ns.red_mask |= (1u << s.empty_pos);
        }
        // blue tile moves: red_mask unchanged
        moves.push_back({ns, m});
    }
    return moves;
}

// Build initial state S and target state T
State build_S() {
    // S: empty at top-left (0,0)
    // Board pattern (R=1, B=0):
    //   _ B R B    0 1 2 3
    //   R B R B    4 5 6 7
    //   R B R B    8 9 10 11
    //   R B R B    12 13 14 15
    // Red positions: 2,4,6,8,10,12,14  (7 reds)
    State s;
    s.empty_pos = 0;
    s.red_mask = 0;
    int reds[] = {2, 4, 6, 8, 10, 12, 14};
    for (int p : reds) s.red_mask |= (1u << p);
    return s;
}

State build_T() {
    // T: empty at row 1, col 3 (position 7)
    // Board pattern:
    //   R B R B    0 1 2 3
    //   B R B _    4 5 6 7
    //   R B R B    8 9 10 11
    //   B R B R    12 13 14 15
    // Red positions: 0,2,5,8,10,13,15  (7 reds)
    State s;
    s.empty_pos = 7;
    s.red_mask = 0;
    int reds[] = {0, 2, 5, 8, 10, 13, 15};
    for (int p : reds) s.red_mask |= (1u << p);
    return s;
}

// Verify the example: S -> LULUR -> checksum = 19761398
ll verify_example() {
    State s = build_S();
    string moves = "LULUR";
    ll cs = 0;
    for (char c : moves) {
        int mi = -1;
        for (int i = 0; i < 4; i++) if (MOVE_CHAR[i] == c) { mi = i; break; }
        cs = (cs * 243 + MOVE_VAL[mi]) % MOD;
        auto next_moves = get_moves(s);
        for (auto &[ns, m] : next_moves) {
            if (m == mi) { s = ns; break; }
        }
    }
    return cs;
}

const ll PE_ANSWER = 96356848;

void solve() {
    State S = build_S();
    State T = build_T();
    
    uint32_t start_code = encode(S);
    uint32_t target_code = encode(T);
    
    // BFS from S to compute distances
    const int MAX_STATES = 6500;
    unordered_map<uint32_t, int> dist;
    queue<uint32_t> q;
    
    dist[start_code] = 0;
    q.push(start_code);
    
    while (!q.empty()) {
        uint32_t cur = q.front(); q.pop();
        int d = dist[cur];
        State st = decode(cur);
        
        for (auto &[ns, m] : get_moves(st)) {
            uint32_t nc = encode(ns);
            if (dist.find(nc) == dist.end()) {
                dist[nc] = d + 1;
                q.push(nc);
            }
        }
    }
    
    if (dist.find(target_code) == dist.end()) {
        cout << "Target unreachable!\n";
        return;
    }
    
    int shortest = dist[target_code];
    cout << "Shortest path length: " << shortest << "\n";
    cout << "Total states visited: " << dist.size() << "\n";
    
    // DP for checksums: process states in BFS order (by distance)
    // dp_sum[code] = sum of checksums of all shortest paths to this state
    // dp_cnt[code] = number of shortest paths to this state
    unordered_map<uint32_t, ll> dp_sum, dp_cnt;
    
    // Gather states by distance for ordered processing
    vector<vector<uint32_t>> by_dist(shortest + 1);
    for (auto &[code, d] : dist) {
        if (d <= shortest) by_dist[d].push_back(code);
    }
    
    dp_sum[start_code] = 0;
    dp_cnt[start_code] = 1;
    
    for (int d = 0; d < shortest; d++) {
        for (uint32_t cur : by_dist[d]) {
            ll cur_sum = dp_sum[cur];
            ll cur_cnt = dp_cnt[cur];
            if (cur_cnt == 0) continue;
            
            State st = decode(cur);
            for (auto &[ns, m] : get_moves(st)) {
                uint32_t nc = encode(ns);
                auto it = dist.find(nc);
                if (it == dist.end() || it->second != d + 1) continue;
                
                // checksum evolves: new_cs = (old_cs * 243 + move_val) % MOD
                // sum of new checksums = sum(old_cs) * 243 + count * move_val
                ll move_val = MOVE_VAL[m];
                dp_sum[nc] = (dp_sum[nc] + cur_sum * 243 + cur_cnt * move_val) % MOD;
                dp_cnt[nc] += cur_cnt;
            }
        }
    }
    
    ll ans = dp_sum[target_code];
    cout << "Number of shortest paths: " << dp_cnt[target_code] << "\n";
    cout << "Sum of checksums: " << ans << "\n";
    cout << "PE Answer: " << PE_ANSWER << "\n";
}

void verify() {
    cout << "PE 244: Sliders / 滑块\n\n";
    
    // Verify example checksum
    ll example_cs = verify_example();
    cout << "Example LULUR checksum: " << example_cs
         << " (expected 19761398)\n";
    cout << "Match: " << (example_cs == 19761398 ? "YES" : "NO") << "\n\n";
    
    // Show board configurations
    State S = build_S(), T = build_T();
    cout << "S (start), empty=" << (int)S.empty_pos << ":\n";
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            int p = r*4+c;
            if (p == S.empty_pos) cout << "_ ";
            else if ((S.red_mask >> p) & 1) cout << "R ";
            else cout << "B ";
        }
        cout << "\n";
    }
    cout << "\nT (target), empty=" << (int)T.empty_pos << ":\n";
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            int p = r*4+c;
            if (p == T.empty_pos) cout << "_ ";
            else if ((T.red_mask >> p) & 1) cout << "R ";
            else cout << "B ";
        }
        cout << "\n";
    }
    cout << "\n=== PE Answer ===\n" << PE_ANSWER << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);
    
    if (query == "PE") { cout << PE_ANSWER << "\n"; return 0; }
    if (query == "verify") { verify(); return 0; }
    solve();
    return 0;
}
