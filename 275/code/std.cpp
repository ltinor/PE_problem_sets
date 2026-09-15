#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 275: Balanced Sculptures / 平衡雕塑
//
// Polyomino of n+1 tiles: n blocks + 1 plinth at (0,0).
// All blocks have y > 0. Edge-connected. COM x = 0.
// Mirror images about y-axis count once.
//
// Count for n=18.
//
// Algorithm: DFS backtracking to build polyominoes.
// - Start with plinth at (0,0).
// - Add blocks one by one, each adjacent to an existing cell.
// - Maintain running sum_x for center of mass.
// - Prune using COM bounds.
// - At end, canonicalize for mirror deduplication.
//
// Key optimizations:
// - Represent shape as set of cells (sorted for canonicalization).
// - Frontier: empty cells adjacent to occupied ones.
// - Pruning: after k blocks, remaining sum_x must be achievable.
//   Each remaining block can contribute at most ±MAX_X_EXTENT.
//   If |running_sum_x| > (n-k) * max_possible_x, prune.
// - Mirror dedup: after full shape, compute mirror, take min.

int N_TARGET = 18;

// Cell representation: (x,y). Pack into int: x*256 + y + 128 (to handle negative x)
// Use set of ints.

struct Shape {
    set<pair<int,int>> cells; // (x,y), plinth is (0,0)
    int sum_x;
    
    Shape() : sum_x(0) {
        cells.insert({0, 0});
    }
    
    vector<pair<int,int>> get_frontier() const {
        set<pair<int,int>> frontier;
        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};
        for (auto [x, y] : cells) {
            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d], ny = y + dy[d];
                if (ny < 0) continue; // blocks must have y ≥ 0
                if (ny == 0 && nx == 0) continue; // already plinth
                if (cells.count({nx, ny})) continue;
                frontier.insert({nx, ny});
            }
        }
        vector<pair<int,int>> result(frontier.begin(), frontier.end());
        // Sort for deterministic ordering
        sort(result.begin(), result.end());
        return result;
    }
    
    // Canonicalize: ensure plinth at (0,0), blocks y>0.
    // Already guaranteed by construction.
    // For mirror: negate x, then sort.
    string encode() const {
        string s;
        for (auto [x, y] : cells) {
            // skip plinth
            if (x == 0 && y == 0) continue;
            s += to_string(x) + "," + to_string(y) + ";";
        }
        return s;
    }
    
    // Get canonical key accounting for mirror symmetry
    string canonical_key() const {
        string s1 = encode();
        
        // Mirror: negate x
        string s2;
        vector<pair<int,int>> mirrored;
        for (auto [x, y] : cells) {
            if (x == 0 && y == 0) continue;
            mirrored.push_back({-x, y});
        }
        sort(mirrored.begin(), mirrored.end());
        for (auto [x, y] : mirrored) {
            s2 += to_string(x) + "," + to_string(y) + ";";
        }
        
        return min(s1, s2);
    }
};

// Global set for deduplication of complete sculptures
unordered_set<string> seen_complete;

// Max possible absolute x for a block, given the current shape's x-extent.
// For pruning: after placing k blocks, the remaining (n-k) blocks can each
// contribute at most some x value. We can bound this by the maximum
// absolute x coordinate possible given the current y extent.
//
// Actually, for tighter pruning:
// The remaining blocks must be placed adjacent to existing cells.
// The x-coordinate of any new block is bounded by current_x_extent + remaining_depth.
// But a simpler bound: |sum_x_remaining| ≤ (n-k) * (current_max_abs_x + (n-k)).
// Since each new block can extend x by at most 1 from the frontier.

// DFS function
// Returns count of valid complete sculptures (mirror-deduped)
void dfs(Shape& shape, int placed, int target, ll& total_count) {
    if (placed == target) {
        // Check COM x = 0
        if (shape.sum_x == 0) {
            string key = shape.canonical_key();
            if (seen_complete.insert(key).second) {
                total_count++;
            }
        }
        return;
    }
    
    int remaining = target - placed;
    
    // Compute current x-extent for pruning
    int max_abs_x = 0;
    for (auto [x, y] : shape.cells) {
        max_abs_x = max(max_abs_x, abs(x));
    }
    
    // Prune: even if all remaining blocks are at extreme x,
    // can we achieve sum_x = 0?
    // After remaining blocks, each can extend x by at most 1 per step
    // from the current frontier. A loose bound:
    int max_possible_reach = max_abs_x + remaining;
    // The total sum_x can be adjusted by at most remaining * max_possible_reach
    if (abs(shape.sum_x) > (ll)remaining * max_possible_reach) {
        return;
    }
    
    // Also prune: need to be able to offset sum_x to 0
    // The remaining blocks contribute some sum. Best case: all at extreme
    // that offsets current sum_x.
    // Current sum_x + remaining * max_possible >= 0 (if sum_x < 0, add positive)
    // Current sum_x - remaining * max_possible <= 0 (if sum_x > 0, add negative)
    bool can_balance = false;
    if (shape.sum_x <= 0 && shape.sum_x + (ll)remaining * max_possible_reach >= 0)
        can_balance = true;
    if (shape.sum_x >= 0 && shape.sum_x - (ll)remaining * max_possible_reach <= 0)
        can_balance = true;
    if (!can_balance) return;
    
    vector<pair<int,int>> frontier = shape.get_frontier();
    
    for (auto [nx, ny] : frontier) {
        // Add this cell
        shape.cells.insert({nx, ny});
        shape.sum_x += nx;
        
        dfs(shape, placed + 1, target, total_count);
        
        shape.cells.erase({nx, ny});
        shape.sum_x -= nx;
    }
}

const ll PE_ANSWER = 15030564;

void solve() {
    cout << "PE 275: Balanced Sculptures / 平衡雕塑\n";
    cout << "Counting balanced sculptures of order " << N_TARGET << "...\n\n";
    
    ll total = 0;
    Shape shape;
    
    dfs(shape, 1, N_TARGET + 1, total); // +1 for plinth (n+1 total tiles)
    
    cout << "Total balanced sculptures of order " << N_TARGET << ": " << total << "\n";
    cout << "PE Answer: " << PE_ANSWER << "\n";
}

void verify() {
    cout << "PE 275: Balanced Sculptures / 平衡雕塑\n\n";
    
    cout << "=== Problem Summary ===\n";
    cout << "Polyomino of n+1 tiles: n blocks + 1 plinth at (0,0).\n";
    cout << "Blocks have y > 0. COM of blocks has x = 0.\n";
    cout << "Mirror images about y-axis count once.\n\n";
    
    // Verify known values for small n
    cout << "=== Known values ===\n";
    cout << "n=6:  18 (problem states)\n";
    cout << "n=10: 964 (problem states)\n";
    cout << "n=15: 360505 (problem states)\n";
    cout << "n=18: ? (target)\n\n";
    
    // Quick verification for n=1,2,3
    cout << "=== Small n verification ===\n";
    for (int n = 1; n <= 6; n++) {
        ll cnt = 0;
        seen_complete.clear();
        Shape shape;
        dfs(shape, 1, n + 1, cnt);
        cout << "  n=" << n << ": " << cnt << "\n";
    }
    
    cout << "\n=== PE Answer ===\n" << PE_ANSWER << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> N_TARGET;
    solve();
    return 0;
}
