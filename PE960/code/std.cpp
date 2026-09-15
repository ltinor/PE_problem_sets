#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 960: Stone Game Solitaire / 石子纸牌游戏
//
// n distinct piles, each with n-1 stones. Initial score = 0.
// Repeat:
//   1. Choose 2 piles, remove exactly n stones total from them.
//   2. If a and b stones removed from the 2 piles, add min(a,b) to score.
// If all piles emptied → final score = accumulated score.
// If stuck (can't empty all) → final score = 0.
//
// F(n) = sum of final scores over all sequences that successfully empty all piles.
//
// Given: F(3)=12, F(4)=360, F(8)=16785941760.
// Find F(100) mod 10^9+7.
//
// Key observations:
// - Each pile initially has n-1 stones.
// - In each move, we remove a total of n stones from 2 piles.
//   Let a from pile i, b from pile j, with a+b = n.
//   Score += min(a, b) = min(a, n-a).
//
// - Total stones initially: n × (n-1) = n(n-1).
//   Each move removes n stones. Total moves needed: n-1 moves.
//   (Since n(n-1)/n = n-1).
//
// - In each move, we remove from exactly 2 piles. Over n-1 moves, we
//   affect 2(n-1) pile-involvements. Since there are n piles, each pile
//   is involved on average 2(n-1)/n = 2 - 2/n times.
//   Some piles are involved multiple times, some fewer.
//
// - The state can be represented by the vector of remaining stones.
//   Initially: (n-1, n-1, ..., n-1).
//
// - Since piles are distinct, sequences of moves matter.
//
// - This is a combinatorial game. Each valid sequence of moves
//   that empties all piles corresponds to a "complete" sequence.
//
// - Let's analyze for small n:
//
// - n=3: 3 piles, each with 2 stones. Total 6 stones. Need 2 moves.
//   Move 1: pick 2 piles (say 1,2), remove a+b=3:
//     Options: (3,0), (2,1), (1,2), (0,3). But pile max is 2, so
//     valid: (2,1), (1,2). Score += min = 1.
//   After (2,1): piles = (0, 1, 2). Now must remove 3 from remaining
//     piles (2 and 3). Options: (1,2) or (2,1) since remaining: pile2=1, pile3=2.
//     If (1,2): piles empty. Score += 1. Total = 2.
//   After (1,2): piles = (1, 0, 2). Similar: remove (1,2) from 1 and 3 → score += 1. Total = 2.
//   But there are 3 choices of which 2 piles to start with. Let's count all:
//
//   Pick piles (1,2): 2 sequences (score 2 each)
//   Pick piles (1,3): 2 sequences
//   Pick piles (2,3): 2 sequences
//   Total: 6 sequences × score 2 = 12. F(3) = 12. ✓
//
// - n=4: 4 piles, each with 3 stones. Total 12 stones. Need 3 moves.
//   This gets more complex. F(4)=360.
//
// - This looks like counting "valid" sequences of moves with weighted scores.
//
// - Alternative view: Represent the process as a sequence of operations
//   where each operation removes n stones total from 2 piles.
//
// - Each sequence defines a binary matrix M (n-1 × n) where M_{t,i}
//   is the number of stones removed from pile i in move t.
//   Each row sums to n. Column i sums to n-1 (initial pile size).
//   M_{t,i} ≥ 0 integers.
//   Score = Σ_t min(M_{t,i}, M_{t,j}) where i,j are the two piles in move t.
//
// - Actually, for each move t, exactly 2 columns have nonzero entries
//   (say columns i and j), and M_{t,i} + M_{t,j} = n.
//
// - This is a combinatorial enumeration of such matrices.
//
// - This is related to "chip-firing" or "sandpile" models, or to
//   counting decompositions of n-1 into n-1 parts for each column.
//
// - Another view: we're pairing the removal of stones. Each stone removal
//   belongs to a specific move. Over the n-1 moves, each pile loses n-1
//   stones. The score for a move (i,j) with removal (a, b) is min(a,b).
//
// - The linearity of expectation suggests: F(n) = total sequences × E[score].
//   But we need exact sum, not expectation.
//
// - Let's count how many sequences are valid. For n=3: 6 sequences. n=4: ?
//   For n=4, we have 3 moves. 4 piles. Let's count total valid sequences.
//
// - This is a known combinatorial object. The answer may involve Catalan
//   numbers or similar combinatorial structures.
//
// - PE answer: (to be computed)

const ll PE_ANSWER = 0; // placeholder
const ll MOD = 1000000007LL;

// Brute force for small n (verification)
ll F_brute(int n) {
    if (n > 5) return 0; // too many states
    
    vector<int> piles(n, n-1);
    ll total_score = 0;
    
    function<void(vector<int>&, ll)> dfs = [&](vector<int>& p, ll score) {
        // Check if all empty
        bool all_zero = true;
        for (int x : p) if (x > 0) { all_zero = false; break; }
        if (all_zero) {
            total_score += score;
            return;
        }
        
        // Check if stuck: no pair sums to n or no move possible
        // Actually we just try all pairs
        for (int i = 0; i < n; i++) {
            if (p[i] == 0) continue;
            for (int j = i+1; j < n; j++) {
                if (p[j] == 0) continue;
                // Try all ways to remove a+b=n from piles i, j
                for (int a = 1; a <= min((int)p[i], n-1); a++) {
                    int b = n - a;
                    if (b > p[j] || b <= 0) continue;
                    p[i] -= a;
                    p[j] -= b;
                    dfs(p, score + min(a, b));
                    p[i] += a;
                    p[j] += b;
                }
            }
        }
    };
    
    dfs(piles, 0);
    return total_score;
}

void verify() {
    cout << "PE 960: Stone Game Solitaire / 石子纸牌游戏\n\n";
    
    cout << "=== Problem Summary ===\n";
    cout << "n piles, each with n-1 stones. Each turn: remove n stones\n";
    cout << "from 2 piles. Score += min(removed). Must empty all piles.\n";
    cout << "F(n) = sum of scores over all successful sequences.\n";
    cout << "F(3)=12, F(4)=360, F(8)=16785941760. Find F(100) mod 1e9+7.\n\n";
    
    cout << "=== Verification ===\n";
    cout << "F(3) = " << F_brute(3) << " (expected 12)\n";
    cout << "F(4) = " << F_brute(4) << " (expected 360)\n\n";
    
    cout << "=== Analysis ===\n";
    cout << "Total moves = n-1. Each move: remove n from 2 piles.\n";
    cout << "Represent as matrix M (n-1 rows × n columns):\n";
    cout << "  Each row has exactly 2 nonzero entries summing to n.\n";
    cout << "  Each column sums to n-1.\n";
    cout << "Score = sum over rows of min(nonzero entries in that row).\n\n";
    
    cout << "=== Target ===\n";
    cout << "F(100) mod 1e9+7. Need combinatorial enumeration.\n\n";
    
    cout << "=== PE Answer ===\n" << PE_ANSWER << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);
    
    if (query == "PE") { cout << PE_ANSWER << "\n"; return 0; }
    if (query == "verify") { verify(); return 0; }
    cout << "PE 960: Stone Game Solitaire / 石子纸牌游戏\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for checks.\n";
    return 0;
}
