#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 936 (simple / OJ reduced-data version) — brute-force reference.
//
// This is the direct enumeration solution: generate every unlabelled (free)
// tree on up to N vertices and count those with no edge joining two vertices
// of equal degree.  Used as the reference against which std.cpp is checked.

vector<vector<string>> rooted;

struct Tree { vector<vector<int>> ch; };

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
        } else {
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

bool peerlessSingle(const Tree& t) {
    int n = (int)t.ch.size();
    vector<int> deg(n);
    for (int i = 0; i < n; i++) deg[i] = (int)t.ch[i].size() + (i == 0 ? 0 : 1);
    for (int u = 0; u < n; u++)
        for (int v : t.ch[u])
            if (deg[u] == deg[v]) return false;
    return true;
}

bool peerlessBi(const Tree& a, const Tree& b) {
    int na = (int)a.ch.size(), nb = (int)b.ch.size();
    vector<int> da(na), db(nb);
    for (int i = 0; i < na; i++) da[i] = (int)a.ch[i].size() + 1;
    for (int i = 0; i < nb; i++) db[i] = (int)b.ch[i].size() + 1;
    for (int u = 0; u < na; u++) for (int v : a.ch[u]) if (da[u] == da[v]) return false;
    for (int u = 0; u < nb; u++) for (int v : b.ch[u]) if (db[u] == db[v]) return false;
    if (da[0] == db[0]) return false;
    return true;
}

void generateRooted(int N) {
    rooted.assign(N + 1, {});
    rooted[1] = {"()"};
    for (int n = 2; n <= N; n++) {
        vector<string> res;
        vector<string> chosen;
        function<void(int, int)> descend = [&](int k, int R) {
            if (R == 0) {
                string s = "(";
                for (auto& c : chosen) s += c;
                s += ")";
                res.push_back(s);
                return;
            }
            if (k == 0) return;
            descend(k - 1, R);
            function<void(int, int, int)> pick_m = [&](int start, int left, int rem) {
                if (left == 0) { descend(k - 1, rem); return; }
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
        rooted[n] = res;
    }
}

ll P(int n) {
    ll cnt = 0;
    for (const string& s : rooted[n]) {
        Tree t = parseTree(s);
        bool centre = true;
        for (int v : t.ch[0])
            if (2 * subtreeSize(t, v) > n - 1) { centre = false; break; }
        if (centre && peerlessSingle(t)) cnt++;
    }
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
