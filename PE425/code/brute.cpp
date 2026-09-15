#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE425 brute: find primes connected to 2 using DSU approach

struct DSU {
    vector<int> parent;
    DSU(int n) : parent(n) { for (int i = 0; i < n; i++) parent[i] = i; }
    int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }
    void unite(int a, int b) { a = find(a); b = find(b); if (a != b) parent[a] = b; }
};

vector<ll> get_neighbors(ll x, ll N) {
    vector<ll> res;
    string s = to_string(x);
    int d = s.size();
    for (int i = 0; i < d; i++) {
        char orig = s[i];
        for (char c = '0'; c <= '9'; c++) {
            if (c == orig) continue;
            if (i == 0 && c == '0') continue;
            s[i] = c;
            ll y = stoll(s);
            if (y <= N && y > 0) res.push_back(y);
        }
        s[i] = orig;
    }
    for (char c = '1'; c <= '9'; c++) {
        ll y = stoll(c + s);
        if (y <= N) res.push_back(y);
    }
    if (d > 1 && s[1] != '0') {
        ll y = stoll(s.substr(1));
        if (y <= N) res.push_back(y);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ll N; cin >> N;
    if (N > 50000) { cout << "0\n"; return 0; }

    vector<bool> is_prime(N + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (ll i = 2; i * i <= N; i++) {
        if (!is_prime[i]) continue;
        for (ll j = i * i; j <= N; j += i) is_prime[j] = false;
    }

    vector<ll> primes;
    for (ll i = 2; i <= N; i++) if (is_prime[i]) primes.push_back(i);

    unordered_map<ll, int> idx;
    for (int i = 0; i < (int)primes.size(); i++) idx[primes[i]] = i;

    vector<pair<ll,ll>> edges;
    for (ll p : primes) {
        for (ll q : get_neighbors(p, N))
            if (is_prime[q] && q > p) edges.push_back({p, q});
    }

    sort(edges.begin(), edges.end(),
         [](auto& a, auto& b) { return a.second < b.second; });

    DSU dsu(primes.size());
    int ep = 0;
    ll sum = 0;

    for (int i = 0; i < (int)primes.size(); i++) {
        ll P = primes[i];
        while (ep < (int)edges.size() && edges[ep].second <= P)
            dsu.unite(idx[edges[ep].first], idx[edges[ep].second]), ep++;
        if (P != 2 && dsu.find(idx[2]) != dsu.find(i)) sum += P;
    }

    cout << sum << "\n";
}
