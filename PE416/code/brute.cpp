#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE416 brute: enumerate all frog paths

void gen_right(int n, int pos, vector<int>& cur, vector<vector<int>>& out) {
    cur.push_back(pos);
    if (pos == n-1) { out.push_back(cur); }
    else { for (int s : {1,2,3}) if (pos+s <= n-1) gen_right(n, pos+s, cur, out); }
    cur.pop_back();
}

void gen_left(int pos, vector<int>& cur, vector<vector<int>>& out) {
    cur.push_back(pos);
    if (pos == 0) { out.push_back(cur); }
    else { for (int s : {1,2,3}) if (pos-s >= 0) gen_left(pos-s, cur, out); }
    cur.pop_back();
}

ll F_brute(ll m, ll n) {
    if (n > 7 || m > 2) return -1;
    vector<vector<int>> rights, lefts;
    { vector<int> c; gen_right(n, 0, c, rights); }
    { vector<int> c; gen_left(n-1, c, lefts); }
    int nr = rights.size(), nl = lefts.size();

    if (m == 1) {
        ll ans = 0;
        for (int i = 0; i < nr; i++)
            for (int j = 0; j < nl; j++) {
                set<int> vis;
                for (int x : rights[i]) vis.insert(x);
                for (int x : lefts[j]) vis.insert(x);
                if ((int)vis.size() >= n-1) ans++;
            }
        return ans;
    }
    // m=2
    ll ans = 0;
    for (int i1 = 0; i1 < nr; i1++)
    for (int j1 = 0; j1 < nl; j1++)
    for (int i2 = 0; i2 < nr; i2++)
    for (int j2 = 0; j2 < nl; j2++) {
        set<int> vis;
        for (int x : rights[i1]) vis.insert(x);
        for (int x : lefts[j1]) vis.insert(x);
        for (int x : rights[i2]) vis.insert(x);
        for (int x : lefts[j2]) vis.insert(x);
        if ((int)vis.size() >= n-1) ans++;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll m, n; cin >> m >> n;
    cout << F_brute(m, n) << "\n";
}
