#include<bits/stdc++.h>
using namespace std;
#define ll long long
// Brute: Fibonacci tree game for small k
// T(k): left=T(k-1), right=T(k-2)
// Game: remove a node + subtree, root is poison
// Grundy analysis for small k

// Compute Grundy values for subtrees
vector<ll> grundy;
ll mex_set(unordered_set<ll>& s) {
    ll m = 0;
    while (s.count(m)) m++;
    return m;
}

// Compute f(k) = number of winning first moves on T(k)
ll f(ll k) {
    if (k == 0) return 0;
    if (k == 1) return 0; // only root, taking it loses
    
    // Brute force for small k: enumerate all nodes
    // T(k) has F(k+2)-1 nodes total, with root at top
    // For brute, we compute via DP/Grundy
    
    // Winning moves are those that make the resulting position a P-position (Grundy=0)
    // When we remove a node's subtree, remaining structure is a forest of Fibonacci trees
    // The Grundy of the whole game is XOR of all component Grundy values
    
    // For small k <= 6, we can brute-enumerate
    // This is a placeholder brute for small k
    return 0;
}

int main() {
    ll k; cin >> k;
    // Precompute Grundy values
    grundy.resize(k+1);
    grundy[0] = 0; // empty tree
    grundy[1] = 0; // single node with poison root -> no winning move
    
    // Actual computation would go here
    // For brute: enumerate all internal nodes
    cout << f(k) << "\n";
}
