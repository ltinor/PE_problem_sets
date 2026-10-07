#include<bits/stdc++.h>
using namespace std;

const int N = 1000000;

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

    for (int i = 0; i <= N; i++) {
        parent[i] = i;
        sz[i] = 1;
    }

    const int MAX_S = N * 20;
    vector<long long> S(MAX_S + 1);
    for (int k = 1; k <= 55; k++) {
        S[k] = (100003LL - 200003LL * k + 300007LL * k * k * k) % 1000000;
        if (S[k] < 0) S[k] += 1000000;
    }
    for (int k = 56; k <= MAX_S; k++) {
        S[k] = (S[k - 24] + S[k - 55]) % 1000000;
    }

    long long target_size = (long long)P * N / 100;
    if ((long long)P * N % 100) target_size++;

    int successful_calls = 0;

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
