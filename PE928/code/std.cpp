#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 928: Cribbage / 克里比奇纸牌
//
// Standard 52-card deck. Hand = non-empty subset of cards.
// Hand score = sum of card values (A=1, J/Q/K=10).
// Cribbage score = pairs(2pts each) + runs(run length pts) + fifteens(2pts each).
// Count hands where Hand score = Cribbage score.
//
// Cards vary only by rank (13 ranks) and suit (4 suits per rank).
// For each rank, we can pick 0-4 cards of that rank.
// Enumerate all 5^13 = 1.22e9 rank-count vectors (feasible with pruning).

const int value[13] = {1,2,3,4,5,6,7,8,9,10,10,10,10};
ll C4[5] = {1, 4, 6, 4, 1};

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);

    if (query == "PE") {
        ll ans = 0;
        int cnt[13];
        
        // Enumerate all rank-count vectors via DFS
        function<void(int, int)> dfs = [&](int idx, int total) {
            if (idx == 13) {
                if (total == 0) return; // empty hand invalid
                
                // Hand score
                int hs = 0;
                ll ways = 1;
                for (int r = 0; r < 13; r++) {
                    hs += cnt[r] * value[r];
                    ways *= C4[cnt[r]];
                }
                
                // Cribbage score
                int crib = 0;
                
                // Pairs: 2*C(c,2) = c*(c-1)
                for (int r = 0; r < 13; r++)
                    crib += cnt[r] * (cnt[r] - 1);
                
                // Runs: maximal consecutive sequences of length ≥3
                for (int r = 0; r < 13; ) {
                    if (cnt[r] == 0) { r++; continue; }
                    int start = r, prod = cnt[r];
                    r++;
                    while (r < 13 && cnt[r] > 0) {
                        prod *= cnt[r];
                        r++;
                    }
                    int len = r - start;
                    if (len >= 3) crib += len * prod;
                }
                
                // Fifteens: DP over ranks counting card-combinations summing to 15
                vector<ll> dp(16, 0);
                dp[0] = 1;
                for (int r = 0; r < 13; r++) {
                    if (cnt[r] == 0) continue;
                    int v = value[r], c = cnt[r];
                    // Precompute C(c,k)
                    vector<ll> choose(c + 1, 0);
                    choose[0] = 1;
                    for (int k = 1; k <= c; k++)
                        choose[k] = choose[k-1] * (c - k + 1) / k;
                    
                    vector<ll> ndp = dp;
                    for (int k = 1; k <= c; k++) {
                        int add = k * v;
                        ll ch = choose[k];
                        for (int s = 0; s + add <= 15; s++)
                            ndp[s + add] += dp[s] * ch;
                    }
                    dp.swap(ndp);
                }
                crib += 2 * (int)dp[15];
                
                if (hs == crib) ans += ways;
                return;
            }
            for (cnt[idx] = 0; cnt[idx] <= 4; cnt[idx]++) {
                dfs(idx + 1, total + cnt[idx]);
            }
        };
        
        dfs(0, 0);
        cout << ans << "\n";
        return 0;
    }

    if (query == "verify") {
        cout << "PE 928: Cribbage / 克里比奇纸牌\n\n";
        cout << "Count hands where Hand score = Cribbage score.\n";
        cout << "Enumerating all 5^13 rank-count vectors.\n";
        cout << "Each with up to C(4,k) suit assignments.\n";
        
        // Quick test: count very small hands
        int cnt[13] = {0};
        int small_ans = 0;
        for (cnt[0] = 0; cnt[0] <= 2; cnt[0]++)
        for (cnt[1] = 0; cnt[1] <= 2; cnt[1]++) {
            int total = cnt[0]+cnt[1];
            if (total == 0) continue;
            int hs = cnt[0]*1 + cnt[1]*2;
            int crib = cnt[0]*(cnt[0]-1) + cnt[1]*(cnt[1]-1); // pairs
            // fifteen: only from 10+5 cards = 15, etc. Not possible with A,2 only
            if (hs == crib) small_ans += C4[cnt[0]] * C4[cnt[1]];
        }
        cout << "Test with only Aces and 2s (up to 2 each): " << small_ans << "\n";
        return 0;
    }

    cout << "PE 928: Cribbage / 克里比奇纸牌\n";
    cout << "Use 'PE' for answer, 'verify' for checks.\n";
    return 0;
}
