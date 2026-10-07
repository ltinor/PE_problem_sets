#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Brute force: try all permutations and check if they follow the rules
// Works for N <= 10 (10! = 3.6M)

// Check if a permutation of seats (perm[i] = position taken at step i)
// follows the rules
bool check_valid(const vector<int>& perm, int N) {
    vector<int> occupied(N + 2, 0); // 1-indexed with sentinels
    // occupied[i] = step number when seat i was taken (0 = empty)
    
    for (int step = 0; step < N; step++) {
        int pos = perm[step];
        
        // Determine what rule applies
        // Rule 1: both adjacent seats (if exist) are empty
        bool rule1_left = (pos == 1) ? true : (occupied[pos-1] == 0);
        bool rule1_right = (pos == N) ? true : (occupied[pos+1] == 0);
        bool rule1 = rule1_left && rule1_right;
        
        // Rule 2: exactly one adjacent seat is occupied
        bool left_occ = (pos > 1) && (occupied[pos-1] > 0);
        bool right_occ = (pos < N) && (occupied[pos+1] > 0);
        bool rule2 = (left_occ ^ right_occ); // exactly one
        
        // Rule 3: otherwise
        
        // Check if there's any seat that could have been taken with higher priority
        int chosen_rule;
        if (rule1) chosen_rule = 1;
        else if (rule2) chosen_rule = 2;
        else chosen_rule = 3;
        
        // Check if any other empty seat has higher priority
        for (int s = 1; s <= N; s++) {
            if (occupied[s] > 0) continue; // occupied
            
            bool s_rule1_left = (s == 1) ? true : (occupied[s-1] == 0);
            bool s_rule1_right = (s == N) ? true : (occupied[s+1] == 0);
            bool s_rule1 = s_rule1_left && s_rule1_right;
            
            bool s_left_occ = (s > 1) && (occupied[s-1] > 0);
            bool s_right_occ = (s < N) && (occupied[s+1] > 0);
            bool s_rule2 = (s_left_occ ^ s_right_occ);
            
            int s_rule = s_rule1 ? 1 : (s_rule2 ? 2 : 3);
            
            if (s_rule < chosen_rule) return false;
        }
        
        occupied[pos] = step + 1;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    ll __ignored_mod; // brute doesn't use mod
    cin >> N >> __ignored_mod;
    
    vector<int> perm(N);
    iota(perm.begin(), perm.end(), 1);
    
    ll cnt = 0;
    do {
        if (check_valid(perm, N)) cnt++;
    } while (next_permutation(perm.begin(), perm.end()));
    
    cout << cnt << "\n";
    return 0;
}
