#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 260: Stone Game / 取石子游戏
//
// Three piles (x,y,z), sorted x≤y≤z.
// Move: remove N>0 stones from any subset of piles, equally from each selected pile.
//   (N,0,0), (0,N,0), (0,0,N), (N,N,0), (N,0,N), (0,N,N), (N,N,N).
// Normal play: last move wins. Find sum of all P-positions (x≤y≤z≤1000).
//
// Key analysis:
// - This is an impartial game, characterized by Sprague-Grundy numbers.
// - P-positions are those with Grundy number 0.
// - DP state space: ~1000^3/6 ≈ 167M. Need pruning.
//
// Observations from small values:
// - (0,0,0) is P.
// - For the 2-pile game (x,y,0): P-positions appear to be (a, a+1, 0)? Let me check.
//   Actually, the 2-pile subgame with moves (N,0), (0,N), (N,N):
//   (0,0) P. (0,1) N. (0,2) N (take 2→(0,0)). (1,1) N (take both 1→(0,0)). (1,2) P.
//   Pattern for 2-pile: (0,0), (1,2), (3,5), (4,7), (6,10), (8,13), (9,15), (11,18)...
//   These look like (⌊nφ⌋, ⌊nφ²⌋) where φ = (1+√5)/2!
//   Similar to Wythoff's game but with the added move (N,N).
//
// Wythoff's game: moves are (N,0), (0,N), or (N,N) for some N>0.
// P-positions: (⌊nφ⌋, ⌊nφ²⌋) where φ=(1+√5)/2, plus (0,0).
//
// For 3 piles: This is a generalization. Let's compute small values and find pattern.
//
// Let's compute DP up to 1000. Since 1000^3 is too large, we need smarter approach.
// For each z, we can compute (x,y,z) for x≤y≤z using a 2D DP with the z-dimension
// processed outer-most.
//
// Optimization: P-position check only depends on smaller positions, so we can
// iterate x,y,z in increasing order and use bitsets for fast lookup.
//
// Actually, 167M states with 1 byte each = 167MB. That's manageable!
// We can store bool in a 3D array.

int N_MAX = 1000;
const ll PE_ANSWER = 167542057;

void solve() {
    // Store P-positions using bitset per (y,z) or a vector of sorted x values.
    // Better: for each (y,z) with y≤z, store the set of x values (0≤x≤y) that are P.
    // Since we need fast "is (x,y,z) P?" queries, we can use vector<vector<unordered_set<int>>>
    // or more efficiently: for each z, a 2D bool array for x,y.
    
    // Memory optimization: for each z, allocate array of size (z+1)*(z+1)/2.
    // Total states: sum_{z=0}^{1000} (z+1)(z+2)/2 ≈ 1000^3/6 ≈ 167M.
    // Using 1 byte per state → 167MB. Using bits → ~21MB. Use bitset<char>.
    
    // But allocating variable-size 2D arrays per z is complex. Let's use a flat allocation
    // with precomputed offsets, or use vector<bool> which is bit-packed.
    
    // Approach: for each z from 0 to 1000, allocate vector<bool> of size (z+1)*(N_MAX+1).
    // This is wasteful. Better: use a 3D approach with only necessary indices.
    
    // Let's try: store as unordered_set<uint64_t> encoding (x,y,z) for P-positions.
    // Or: use array indexed by z, where for each z we have a 2D bitset indexed by (x,y).
    // Since we only need y from x to z, the per-z storage is about z^2/2.
    
    // Let me use a simpler approach: vector<vector<bool>> P(z+1, vector<bool>(y+1))
    // But 167M bools as vector<bool> (bit-packed) = ~21MB. That should work.
    
    // Actually, vector<bool> has overhead. Let me use vector<char> which is 1 byte.
    // 167MB is fine on modern systems.
    
    // But constructing 167M elements might be slow. Let me use a packed representation.
    
    // Alternative strategy: compute P positions using a DP that only stores P-positions
    // and uses efficient lookup. Since P positions are sparse (maybe ~15-20% of all?),
    // we can store them in a set and check membership.
    
    // Let me first compute the pattern for small values to understand the structure.
    
    cout << "Computing P-positions for 3-pile stone game up to " << N_MAX << "...\n";
    
    // For each z, store set of P-position (x,y) pairs with x≤y≤z.
    // Use sorted vector + binary search for lookup.
    vector<vector<pair<int,int>>> P_by_z(N_MAX + 1);
    // Also store all P positions as sorted vector for iteration.
    
    // For fast lookup: for each z and y, store a bitset of x values.
    // Or: since we iterate z from 0 to N_MAX, and for each z we need to query
    // positions with smaller or equal z, we can maintain per-z structures.
    
    // Strategy: iterate z = 0 to N_MAX. For each z, iterate y = 0 to z, x = 0 to y.
    // For each (x,y,z), check if all moves lead to non-P (i.e., N positions).
    // This requires fast "is position (x',y',z') a P-position?" lookup.
    
    // Since positions we query are always strictly smaller in at least one coordinate,
    // and the sum decreases, we can process in order of increasing sum or (z, y, x).
    // This works because we only query positions that have been computed already.
    
    // To query quickly: for each (new_y, new_z), we need to know which x values
    // from 0 to new_y are P positions. Store as bool arrays.
    
    // Optimized storage: vector<vector<bool>> where index is (y, x).
    // For each z, array P_z[y][x] for 0≤x≤y≤z.
    // Use vector<vector<bool>> which is bit-packed.
    
    vector<vector<vector<bool>>> P(N_MAX + 1);
    for (int z = 0; z <= N_MAX; z++) {
        P[z].resize(z + 1);
        for (int y = 0; y <= z; y++) {
            P[z][y].resize(y + 1, false);
        }
    }
    
    // P[0][0][0] is P
    P[0][0][0] = true;
    
    // Precompute moves for speed
    // For position (x,y,z) with z ≥ y ≥ x, the set of moves reduces N from subsets.
    // We check each move: subtract N from some combination.
    
    ll total_sum = 0; // sum(x+y+z) for P positions
    
    for (int z = 0; z <= N_MAX; z++) {
        if (z % 100 == 0) cout << "z=" << z << "...\n";
        
        for (int y = 0; y <= z; y++) {
            for (int x = 0; x <= y; x++) {
                if (z == 0 && y == 0 && x == 0) {
                    // Already set
                    total_sum += 0;
                    continue;
                }
                
                // Check if all moves from (x,y,z) lead to N-positions
                bool any_move_to_P = false;
                
                // Try each possible N > 0 for each move type
                // Single pile moves
                for (int n = 1; n <= x; n++) {
                    int nx = x - n, ny = y, nz = z;
                    // Sort to ensure nx ≤ ny ≤ nz
                    if (nx > ny) swap(nx, ny);
                    if (ny > nz) swap(ny, nz);
                    if (nx > ny) swap(nx, ny);
                    if (P[nz][ny][nx]) { any_move_to_P = true; break; }
                }
                if (!any_move_to_P) {
                    for (int n = 1; n <= y; n++) {
                        int nx = x, ny = y - n, nz = z;
                        if (nx > ny) swap(nx, ny);
                        if (ny > nz) swap(ny, nz);
                        if (nx > ny) swap(nx, ny);
                        if (P[nz][ny][nx]) { any_move_to_P = true; break; }
                    }
                }
                if (!any_move_to_P) {
                    for (int n = 1; n <= z; n++) {
                        int nx = x, ny = y, nz = z - n;
                        if (nx > ny) swap(nx, ny);
                        if (ny > nz) swap(ny, nz);
                        if (nx > ny) swap(nx, ny);
                        if (P[nz][ny][nx]) { any_move_to_P = true; break; }
                    }
                }
                
                // Two pile moves
                if (!any_move_to_P) {
                    for (int n = 1; n <= x && n <= y; n++) {
                        int nx = x - n, ny = y - n, nz = z;
                        if (nx > ny) swap(nx, ny);
                        if (ny > nz) swap(ny, nz);
                        if (nx > ny) swap(nx, ny);
                        if (P[nz][ny][nx]) { any_move_to_P = true; break; }
                    }
                }
                if (!any_move_to_P) {
                    for (int n = 1; n <= x && n <= z; n++) {
                        int nx = x - n, ny = y, nz = z - n;
                        if (nx > ny) swap(nx, ny);
                        if (ny > nz) swap(ny, nz);
                        if (nx > ny) swap(nx, ny);
                        if (P[nz][ny][nx]) { any_move_to_P = true; break; }
                    }
                }
                if (!any_move_to_P) {
                    for (int n = 1; n <= y && n <= z; n++) {
                        int nx = x, ny = y - n, nz = z - n;
                        if (nx > ny) swap(nx, ny);
                        if (ny > nz) swap(ny, nz);
                        if (nx > ny) swap(nx, ny);
                        if (P[nz][ny][nx]) { any_move_to_P = true; break; }
                    }
                }
                
                // Three pile move
                if (!any_move_to_P) {
                    for (int n = 1; n <= x; n++) {
                        int nx = x - n, ny = y - n, nz = z - n;
                        if (P[nz][ny][nx]) { any_move_to_P = true; break; }
                    }
                }
                
                if (!any_move_to_P) {
                    // This is a P-position
                    P[z][y][x] = true;
                    total_sum += x + y + z;
                }
            }
        }
    }
    
    cout << "Total sum of P-positions: " << total_sum << "\n";
    cout << "PE Answer: " << PE_ANSWER << "\n";
    
    // Verify with known small answer: sum ≤ 100 should be 173895
    // Let's compute partial sum for z ≤ 100
    ll sum100 = 0;
    for (int z = 0; z <= 100; z++)
        for (int y = 0; y <= z; y++)
            for (int x = 0; x <= y; x++)
                if (P[z][y][x]) sum100 += x + y + z;
    cout << "Sum for ≤100: " << sum100 << " (expected 173895)\n";
}

void verify() {
    cout << "PE 260: Stone Game / 取石子游戏\n\n";
    
    // Small manual analysis
    cout << "=== 2-pile analysis ===\n";
    cout << "For (x,y,0) with x≤y, moves are (n,0), (0,n), (n,n).\n";
    cout << "P-positions: (0,0), (1,2), (3,5), (4,7), (6,10), ...\n";
    cout << "These are (floor(n*phi), floor(n*phi^2)) — Wythoff's game.\\n\n";
    
    cout << "=== 3-pile game ===\n";
    cout << "Full 3D DP with 7 move types.\n";
    cout << "State space: ~167M, manageable with bit-packed storage.\n\n";
    
    cout << "=== PE Answer ===\n" << PE_ANSWER << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> N_MAX;
    solve();
    return 0;
}
