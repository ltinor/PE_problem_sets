#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// BFS: find smallest multiple of n using only digits 0,1,2
// We build numbers by appending digits 0,1,2
// Track visited remainders mod n
ll f(ll n) {
    if (n == 1) return 1;
    // BFS: queue of (remainder, number_as_string_length)
    // But numbers get huge, so we track (remainder, first_digit, parent_remainder)
    // to reconstruct the number
    vector<int> parent(n, -1);   // which remainder we came from
    vector<int> digit(n, -1);    // which digit was added
    vector<int> dist(n, -1);     // BFS distance

    queue<int> q;
    // Start with digits 1 and 2
    for (int d = 1; d <= 2; d++) {
        int r = d % n;
        if (parent[r] == -1) {
            parent[r] = -2; // root marker
            digit[r] = d;
            dist[r] = 1;
            q.push(r);
            if (r == 0) {
                return d / n;
            }
        }
    }

    while (!q.empty()) {
        int r = q.front(); q.pop();
        // Append 0, 1, 2
        for (int d = 0; d <= 2; d++) {
            int nr = (r * 10 + d) % n;
            if (parent[nr] == -1) {
                parent[nr] = r;
                digit[nr] = d;
                dist[nr] = dist[r] + 1;
                q.push(nr);
                if (nr == 0) {
                    // Reconstruct the number
                    // We need the full number, but it may overflow 64-bit
                    // Instead, we can reconstruct using strings
                    // But for f(n)/n, we need the quotient which also may overflow
                    // We'll use __int128
                    string s;
                    int cur = 0;
                    while (cur != -2) {
                        s += char('0' + digit[cur]);
                        cur = parent[cur];
                    }
                    reverse(s.begin(), s.end());
                    // Convert to __int128
                    __int128 val = 0;
                    for (char c : s) {
                        val = val * 10 + (c - '0');
                    }
                    return (ll)(val / n); // return f(n)/n
                }
            }
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    __int128 sum = 0;
    for (ll n = 1; n <= N; n++) {
        sum += f(n);
    }

    // Output as string for large values
    string ans;
    if (sum == 0) ans = "0";
    while (sum > 0) {
        ans = char('0' + (int)(sum % 10)) + ans;
        sum /= 10;
    }
    cout << ans << "\n";

    return 0;
}
