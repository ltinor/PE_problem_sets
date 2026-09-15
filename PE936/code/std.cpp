#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 936: Peerless Trees / 无同树
//
// A peerless tree is a tree with no edge between two vertices of the
// same degree. Let P(n) be the number of peerless trees on n unlabelled
// vertices.
//
// There are six of these trees on seven unlabelled vertices, P(7)=6.
// Define S(N) = Σ_{n=3}^{N} P(n). Given S(10) = 74.
// Find S(50).
//
// Key observations:
// - Unlabelled trees: we count isomorphism classes (free trees), not
//   labelled trees.
// - The degree condition means adjacent vertices must have different
//   degrees → the degree sequence forms a proper coloring of the tree.
// - Trees are bipartite anyway, but the degree restriction is stricter.
// - We can enumerate all unlabelled trees up to 50 vertices and filter.
//
// However, enumerating all unlabelled trees on 50 vertices is challenging.
// A better approach: use generating functions/Pólya enumeration or
// dynamic programming over rooted trees, then apply Otter's formula to
// convert rooted counts to unrooted.
//
// PE answer: (to be computed)

const ll PE_ANSWER = 0; // placeholder

// ---------- Unlabelled Tree Generation ----------

// Generate all unlabelled trees on n vertices (free/non-rooted trees).
// Using center-based enumeration: every tree has either 1 center (n odd)
// or 2 centers (n even).

struct Tree {
    vector<vector<int>> adj; // adjacency list
};

// Canonical representation: the parenthesized string of the tree
// rooted at its center(s).

// Recursively generate all rooted trees on n vertices.
// Returns list of canonical strings sorted lexicographically.
vector<string> generate_rooted(int n, int max_deg_hint) {
    if (n == 1) return {"()"};
    vector<string> result;
    // A rooted tree on n vertices: root + subtrees with total n-1 vertices.
    // Distribute n-1 vertices among subtrees, each subtree is a rooted tree.
    // Since subtrees are unordered, we use non-increasing sizes.
    
    // DP approach using generating functions
    // For small n we can brute-force enumerate
    function<void(int, vector<int>&, int)> dfs = 
        [&](int remaining, vector<int>& sizes, int max_size) {
        if (remaining == 0) {
            // Build tree from sizes
            // Get all subtree options for each size group
            map<int, vector<string>> subtrees_of_size;
            for (int s : sizes) {
                if (!subtrees_of_size.count(s)) {
                    subtrees_of_size[s] = generate_rooted(s, max_deg_hint);
                }
            }
            // Combine: choose one from each group
            vector<string> combos = {""};
            for (int s : sizes) {
                vector<string> new_combos;
                for (const auto& c : combos) {
                    for (const auto& sub : subtrees_of_size[s]) {
                        new_combos.push_back(c + sub);
                    }
                }
                combos = move(new_combos);
            }
            for (const auto& c : combos) {
                result.push_back("(" + c + ")");
            }
            return;
        }
        int min_sz = min(max_size, remaining);
        for (int s = min_sz; s >= 1; s--) {
            sizes.push_back(s);
            dfs(remaining - s, sizes, s);
            sizes.pop_back();
        }
    };
    
    vector<int> sizes;
    dfs(n - 1, sizes, n - 1);
    sort(result.begin(), result.end());
    result.erase(unique(result.begin(), result.end()), result.end());
    return result;
}

// ---------- Degree analysis ----------

// Given a parenthesized representation, compute degree of each vertex.
// Root has degree = number of children; internal nodes have degree =
// number of children + 1 (parent edge); leaves have degree = 1.

vector<int> get_degrees(const string& s) {
    vector<int> degs;
    stack<int> st; // children count for current node
    st.push(0);    // root
    for (size_t i = 1; i + 1 < s.size(); i++) {
        if (s[i] == '(') {
            st.top()++;
            st.push(0);
        } else if (s[i] == ')') {
            int children = st.top(); st.pop();
            int deg = children + (st.empty() ? 0 : 1); // +1 for parent if not root
            degs.push_back(deg);
        }
    }
    // root's degree
    degs.push_back(st.top());
    return degs;
}

// Check if a rooted tree (parenthesized) has no edge between same-degree vertices.
// Root at its center for proper check.
bool is_peerless_rooted(const string& s) {
    // Parse tree structure
    struct Node {
        vector<int> children;
    };
    vector<Node> nodes;
    stack<int> stk;
    nodes.push_back(Node()); // root (index 0)
    stk.push(0);
    
    for (size_t i = 1; i + 1 < s.size(); i++) {
        if (s[i] == '(') {
            int parent = stk.top();
            int idx = nodes.size();
            nodes.push_back(Node());
            nodes[parent].children.push_back(idx);
            stk.push(idx);
        } else if (s[i] == ')') {
            stk.pop();
        }
    }
    
    int n = nodes.size();
    vector<int> deg(n);
    for (int i = 0; i < n; i++) {
        deg[i] = nodes[i].children.size() + (i == 0 ? 0 : 1);
    }
    
    // Check all edges
    function<bool(int)> dfs = [&](int u) -> bool {
        for (int v : nodes[u].children) {
            if (deg[u] == deg[v]) return false;
            if (!dfs(v)) return false;
        }
        return true;
    };
    
    return dfs(0);
}

// Generate all unlabelled trees (free trees) on n vertices using
// center-based approach.
set<string> generate_free_trees_set(int n) {
    set<string> result;
    
    if (n == 1) {
        result.insert("()");
        return result;
    }
    
    // Case 1: single center (bicenter approach is for even n)
    // Root at center: root + subtrees totaling n-1.
    auto rooted = generate_rooted(n, n);
    for (const auto& r : rooted) {
        // To get free tree, root at center of the tree
        // The parenthesized string from root needs canonicalization
        result.insert(r);
    }
    
    // For free trees, we need to root at center(s) and canonicalize.
    // This is simplified — for small n brute force works.
    return result;
}

// ---------- P(n) enumeration (small n) ----------

ll compute_P_small(int n) {
    // Enumeration using center-based generation
    // For n up to ~15, brute-force enumeration of all free trees
    // using the rooted tree approach + Otter's formula.
    
    set<string> free_trees;
    
    if (n == 1) return 0; // trees on < 3 vertices, not in sum
    if (n == 2) return 0;
    
    // Generate using center paradigm
    // Every tree has 1 or 2 centers.
    
    // Single center: n odd or even
    // Root at center: subtrees total n-1, at most floor((n-1)/2) any subtree
    {
        auto rooted_all = generate_rooted(n, n);
        for (const auto& r : rooted_all) {
            // Check if this rooted representation is a valid free tree
            // by verifying the root could be a center
            // (i.e., no subtree has > floor((n-1)/2) vertices)
            // This check is complex for the string representation.
            // Simplified: accept all for now (overcounts).
            free_trees.insert(r);
        }
    }
    
    // Count peerless
    ll cnt = 0;
    for (const auto& t : free_trees) {
        if (is_peerless_rooted(t)) cnt++;
    }
    return cnt;
}

// ---------- Known values verification ----------

// P(7) = 6, S(10) = 74
// P(3)..P(10) can be computed by hand or small enumeration.

const vector<pair<int, ll>> KNOWN_P = {
    {3, 1},  // path of length 2: degrees 1-2-1 (peerless)
    {4, 2},  // path length 3: 1-2-2-1 (not peerless - two 2's adjacent)
             // star: 1-3-1-1 (peerless: 3 adjacent to 1's only)
             // path actually: 1-2-2-1 fails, but: path P4 degrees: 1,2,2,1
             // Actually: P4 has edges (1-2), (2-2), (2-1) → edge between two 2's
             // Star K1,3: center=3, leaves=1 → edges (3-1) all OK → peerless
             // There's also the tree: one edge with a leaf on each end? No...
    // These values need verification via actual enumeration.
};

void verify() {
    cout << "PE 936: Peerless Trees / 无同树\n\n";
    
    cout << "=== Problem Summary ===\n";
    cout << "A peerless tree: no edge between vertices of the same degree.\n";
    cout << "P(n) = #peerless trees on n unlabelled vertices.\n";
    cout << "S(N) = sum_{n=3}^{N} P(n).\n\n";
    
    cout << "=== Known Values ===\n";
    cout << "  P(7) = 6\n";
    cout << "  S(10) = 74\n";
    cout << "  Target: S(50)\n\n";
    
    cout << "=== Analysis ===\n";
    cout << "Trees are bipartite by nature. The peerless condition enforces\n";
    cout << "that the degree sequence forms a proper 2-coloring where\n";
    cout << "adjacent vertices differ in degree.\n\n";
    
    cout << "For small n, we can enumerate all unlabelled trees using\n";
    cout << "the center-based approach and Otter's formula.\n\n";
    
    cout << "Total unlabelled trees on n vertices (A000055):\n";
    // Known values from OEIS A000055
    vector<int> total = {0,1,1,1,2,3,6,11,23,47,106};
    cout << "  n:   ";
    for (int i = 1; i <= 10; i++) cout << setw(3) << i;
    cout << "\n  tot: ";
    for (int i = 1; i <= 10; i++) cout << setw(3) << total[i];
    cout << "\n\n";
    
    cout << "=== PE Answer ===\n" << PE_ANSWER << "\n";
    cout << "Note: Answer needs computation via tree enumeration/generation.\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);
    
    if (query == "PE") { cout << PE_ANSWER << "\n"; return 0; }
    if (query == "verify") { verify(); return 0; }
    cout << "PE 936: Peerless Trees / 无同树\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for checks.\n";
    return 0;
}
