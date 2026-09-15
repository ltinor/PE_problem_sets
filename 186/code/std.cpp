#include<bits/stdc++.h>
using namespace std;
#define ll long long

const int N = 1000000;

// DSU
int parent[N + 1];
int sz[N + 1];

int find(int x) {
    return parent[x] == x ? x : parent[x] = find(parent[x]);
}

void unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return;
    if (sz[a] < sz[b]) swap(a, b);
    parent[b] = a;
    sz[a] += sz[b];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int P, T;
    cin >> P >> T;

    // Init DSU
    for (int i = 0; i <= N; i++) {
        parent[i] = i;
        sz[i] = 1;
    }

    // Lagged Fibonacci generator: S_k
    // Need enough values: answer ~2.3M successful calls, each using 2 S values
    const int MAX_S = N * 20;
    vector<ll> S(MAX_S + 1);
    for (int k = 1; k <= 55; k++) {
        S[k] = (100003LL - 200003LL * k + 300007LL * k * k * k) % 1000000;
        if (S[k] < 0) S[k] += 1000000;
    }
    for (int k = 56; k <= MAX_S; k++) {
        S[k] = (S[k - 24] + S[k - 55]) % 1000000;
    }

    ll target_size = (ll)P * N / 100;
    if ((ll)P * N % 100) target_size++;

    int successful_calls = 0;

    // Process phone calls: misdial when caller == called
    for (int k = 1; ; k++) {
        int caller = S[2 * k - 1];
        int called = S[2 * k];

        if (caller != called) {
            successful_calls++;
            unite(caller, called);
            if (sz[find(T)] >= target_size) {
                cout << successful_calls << "\n";
                return 0;
            }
        }
    }

    return 0;
}
