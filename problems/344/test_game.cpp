#include<bits/stdc++.h>
using namespace std;

// Game on n squares, positions 1..n
// pos: sorted coin positions (c+1 total), sd: index of silver dollar (0..c)
// State: bitmask of coins remaining? No, just track coin positions.

map<vector<int>, int> memo; // pos -> winner (1 = first player wins)

int grundy(const vector<int>& pos, int sd, int n) {
    // pos: positions of remaining coins (sorted)
    // sd: index in pos of silver dollar
    // Returns 1 if current player can force a win
    
    if (pos.size() == 1) {
        // Only silver dollar left, current player pockets it and wins
        return 1;
    }
    
    // Try all possible moves
    // Regular moves: move any coin left
    for (int i = 0; i < (int)pos.size(); i++) {
        int left_bound = (i == 0) ? 1 : pos[i-1] + 1;
        for (int new_pos = pos[i] - 1; new_pos >= left_bound; new_pos--) {
            vector<int> new_positions = pos;
            new_positions[i] = new_pos;
            sort(new_positions.begin(), new_positions.end());
            
            // Find new sd index
            int new_sd = -1;
            for (int j = 0; j < (int)new_positions.size(); j++) {
                if (new_positions[j] == pos[sd]) { new_sd = j; break; }
            }
            // Actually the silver dollar moves, so its position changes
            // The coin that's the silver dollar has position pos[sd].
            // If we moved the silver dollar (i == sd):
            if (i == sd) {
                new_sd = -1;
                for (int j = 0; j < (int)new_positions.size(); j++) {
                    if (new_positions[j] == new_pos) { new_sd = j; break; }
                }
            } else {
                new_sd = -1;
                for (int j = 0; j < (int)new_positions.size(); j++) {
                    if (new_positions[j] == pos[sd]) { new_sd = j; break; }
                }
            }
            
            if (new_sd == -1) continue; // shouldn't happen
            
            // Recursive call
            int result = grundy(new_positions, new_sd, n);
            if (result == 0) return 1; // Found a winning move
        }
    }
    
    // Special move: pocket leftmost coin
    if (pos[0] == pos[sd]) {
        // Leftmost is silver dollar, current player wins by pocketing it
        return 1;
    }
    // Remove leftmost coin
    vector<int> new_pos(pos.begin() + 1, pos.end());
    int new_sd = sd - 1; // silver dollar shifts left in index
    if (grundy(new_pos, new_sd, n) == 0) return 1;
    
    // If no winning move found, current player loses
    return 0;
}

int main() {
    int n = 10, c = 2;
    int tc = c + 1; // 3 coins
    
    int winning = 0;
    
    // Enumerate all C(n, tc) combinations
    vector<int> comb(tc);
    iota(comb.begin(), comb.end(), 1);
    
    while (true) {
        // For each silver dollar position
        for (int sd = 0; sd < tc; sd++) {
            memo.clear();
            int result = grundy(comb, sd, n);
            if (result == 1) winning++;
        }
        
        // Next combination
        int i;
        for (i = tc - 1; i >= 0; i--) {
            if (comb[i] < n - tc + 1 + i) break;
        }
        if (i < 0) break;
        comb[i]++;
        for (int j = i + 1; j < tc; j++) {
            comb[j] = comb[j-1] + 1;
        }
    }
    
    cout << "W(10,2) = " << winning << " (expected 324)" << endl;
    return 0;
}
