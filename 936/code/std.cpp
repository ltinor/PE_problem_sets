#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 936 (simple / OJ reduced-data version): Peerless Trees / 无同树
//
// A "peerless tree" is a tree with no edge between two vertices of the same
// degree.  Let P(n) be the number of peerless trees on n *unlabelled*
// vertices, and S(N) = sum_{n=3}^{N} P(n).
//
// Given: P(7) = 6, S(10) = 74.  (The original problem asks for S(50).)
//
// Simple version: N is reduced so that enumerating all unlabelled (free)
// trees is feasible.  We generate every free tree on up to N vertices and
// count the peerless ones.
//
// Free trees are enumerated by the standard centre decomposition:
//   * single-centre trees  <=>  rooted trees of size n in which every child
//     subtree of the root has size <= (n-1)/2 (i.e. the root is the centre);
//   * bicentre trees (n even)  <=>  unordered pairs of rooted trees of size
//     n/2 whose roots are joined by one edge.
//
// Every rooted tree is stored as a canonical balanced-parentheses string
// (children sorted by descending size, then by ascending string), so each
// isomorphism class appears exactly once.

// ---------- rooted tree canonical strings ----------

vector<vector<string>> rooted; // rooted[s] = all non-isomorphic rooted trees on s vertices

struct Tree {
    vector<vector<int>> ch;
    int size() const { return (int)ch.size(); }
};

Tree parseTree(const string& s) {
    Tree t;
    t.ch.push_back({});
    vector<int> st = {0};
    for (size_t i = 1; i < s.size(); i++) {
        if (s[i] == '(') {
            int p = st.back();
            t.ch.push_back({});
            int id = (int)t.ch.size() - 1;
            t.ch[p].push_back(id);
            st.push_back(id);
        } else { // ')'
            st.pop_back();
        }
    }
    return t;
}

int subtreeSize(const Tree& t, int u) {
    int s = 1;
    for (int v : t.ch[u]) s += subtreeSize(t, v);
    return s;
}

// Peerless check for a single-centre rooted tree (root = centre).
// degree[root] = #children, degree[others] = #children + 1.
bool peerlessSingle(const Tree& t) {
    int n = t.size();
    vector<int> deg(n);
    for (int i = 0; i < n; i++) deg[i] = (int)t.ch[i].size() + (i == 0 ? 0 : 1);
    for (int u = 0; u < n; u++)
        for (int v : t.ch[u])
            if (deg[u] == deg[v]) return false;
    return true;
}

// Peerless check for a bicentre tree formed by joining the roots of a and b.
// Every vertex then has degree = #children + 1 (the two roots count the
// joining edge as their "+1", all others count their parent).
bool peerlessBi(const Tree& a, const Tree& b) {
    int na = a.size(), nb = b.size();
    vector<int> da(na), db(nb);
    for (int i = 0; i < na; i++) da[i] = (int)a.ch[i].size() + 1;
    for (int i = 0; i < nb; i++) db[i] = (int)b.ch[i].size() + 1;
    for (int u = 0; u < na; u++) for (int v : a.ch[u]) if (da[u] == da[v]) return false;
    for (int u = 0; u < nb; u++) for (int v : b.ch[u]) if (db[u] == db[v]) return false;
    if (da[0] == db[0]) return false; // the joining edge between the two roots
    return true;
}

// Generate all non-isomorphic rooted trees on 1..N vertices.
void generateRooted(int N) {
    rooted.assign(N + 1, {});
    rooted[1] = {"()"};
    for (int n = 2; n <= N; n++) {
        vector<string> res;
        vector<string> chosen;

        // Choose the multiset of children of the root (total size n-1).
        // Sizes are considered in descending order; within one size the
        // trees are picked in ascending string order -> canonical form.
        function<void(int, int)> descend = [&](int k, int R) {
            if (R == 0) {
                string s = "(";
                for (auto& c : chosen) s += c;
                s += ")";
                res.push_back(std::move(s));
                return;
            }
            if (k == 0) return;
            descend(k - 1, R); // no tree of size k

            function<void(int, int, int)> pick_m = [&](int start, int left, int rem) {
                if (left == 0) {
                    descend(k - 1, rem);
                    return;
                }
                for (int i = start; i < (int)rooted[k].size(); i++) {
                    if (k > rem) break;
                    chosen.push_back(rooted[k][i]);
                    pick_m(i, left - 1, rem - k);
                    chosen.pop_back();
                }
            };
            for (int m = 1; m * k <= R; m++) pick_m(0, m, R);
        };
        descend(n - 1, n - 1);

        sort(res.begin(), res.end());
        res.erase(unique(res.begin(), res.end()), res.end());
        rooted[n] = std::move(res);
    }
}

ll P(int n) {
    ll cnt = 0;

    // Single-centre trees: rooted trees of size n whose root is the centre.
    for (const string& s : rooted[n]) {
        Tree t = parseTree(s);
        bool centre = true;
        for (int v : t.ch[0]) {
            if (2 * subtreeSize(t, v) > n - 1) { centre = false; break; }
        }
        if (centre && peerlessSingle(t)) cnt++;
    }

    // Bicentre trees (n even): unordered pairs of rooted trees of size n/2.
    if (n % 2 == 0) {
        int h = n / 2;
        const vector<string>& R = rooted[h];
        for (int i = 0; i < (int)R.size(); i++)
            for (int j = i; j < (int)R.size(); j++)
                if (peerlessBi(parseTree(R[i]), parseTree(R[j]))) cnt++;
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N;
    if (!(cin >> N)) return 0;

    generateRooted(max(N, 2));

    ll S = 0;
    for (int n = 3; n <= N; n++) S += P(n);
    cout << S << "\n";
    return 0;
}
