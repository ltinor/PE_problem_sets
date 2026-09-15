#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Brute force for PE 321: compute M(n) for small n via BFS
// n red counters on left, n blue on right, 1 empty center
// Total 2n+1 positions. State represented as string of length 2n+1
// 'R'=red, 'B'=blue, '.'=empty

bool is_triangle(ll x) {
    // x = k(k+1)/2 => 8x+1 is perfect square
    ll d = (ll)sqrt(8*x + 1);
    return d*d == 8*x + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    cin >> K; // K terms to find

    vector<int> terms;
    for (int n = 1; terms.size() < (size_t)K; n++) {
        int len = 2*n + 1;
        // Initial state: n R's, then '.', then n B's
        string start = string(n, 'R') + "." + string(n, 'B');
        string target = string(n, 'B') + "." + string(n, 'R');

        // BFS
        map<string, int> dist;
        queue<string> q;
        dist[start] = 0;
        q.push(start);

        while (!q.empty()) {
            string s = q.front(); q.pop();
            int d = dist[s];
            if (s == target) {
                if (is_triangle(d)) {
                    terms.push_back(n);
                }
                break;
            }

            int empty_pos = s.find('.');
            // Slide: move counter from adjacent square into empty
            if (empty_pos > 0) {
                string t = s;
                swap(t[empty_pos], t[empty_pos - 1]);
                if (!dist.count(t)) {
                    dist[t] = d + 1;
                    q.push(t);
                }
            }
            if (empty_pos < len - 1) {
                string t = s;
                swap(t[empty_pos], t[empty_pos + 1]);
                if (!dist.count(t)) {
                    dist[t] = d + 1;
                    q.push(t);
                }
            }
            // Hop: jump over one counter
            if (empty_pos > 1) {
                string t = s;
                swap(t[empty_pos], t[empty_pos - 2]);
                if (!dist.count(t)) {
                    dist[t] = d + 1;
                    q.push(t);
                }
            }
            if (empty_pos < len - 2) {
                string t = s;
                swap(t[empty_pos], t[empty_pos + 2]);
                if (!dist.count(t)) {
                    dist[t] = d + 1;
                    q.push(t);
                }
            }
        }
    }

    ll sum = 0;
    for (int x : terms) sum += x;
    cout << sum << "\n";
    return 0;
}
