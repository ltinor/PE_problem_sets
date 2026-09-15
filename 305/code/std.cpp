#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// Find k-th occurrence position of m in S
ll find_kth_occurrence(ll m, ll k) {
    string ms = to_string(m);
    int L = ms.length();

    // We'll scan S incrementally, keeping a sliding window of characters
    // to detect cross-boundary matches
    string window; // last L-1 chars of previous numbers, for boundary detection
    ll pos = 1;     // current position in S (1-indexed)
    ll occ = 0;

    for (ll num = 1; ; num++) {
        string ns = to_string(num);
        int nlen = ns.length();

        // Check within current number
        for (int i = 0; i + L <= nlen; i++) {
            if (ns.substr(i, L) == ms) {
                occ++;
                if (occ == k) return pos + i;
            }
        }

        // Check cross-boundary: combine window tail + current number prefix
        string combined = window + ns;
        // For each starting position in window that could reach into ns
        int wlen = window.length();
        for (int i = 0; i < wlen; i++) {
            if (i + L <= (int)combined.length()) {
                if (combined.substr(i, L) == ms) {
                    // This occurrence starts at (pos - wlen + i)
                    occ++;
                    if (occ == k) return pos - wlen + i;
                }
            }
        }

        // Update window: keep last L-1 chars
        if (nlen >= L - 1) {
            window = ns.substr(nlen - (L - 1));
        } else {
            window = window + ns;
            if (window.length() > L - 1)
                window = window.substr(window.length() - (L - 1));
        }

        pos += nlen;

        // Safety limit for huge scans
        if (pos > 100000000000LL) break;
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll K;
    cin >> K;

    i128 sum = 0;
    for (ll k = 1; k <= K; k++) {
        ll m = 1;
        for (ll i = 0; i < k; i++) m *= 3; // 3^k
        ll p = find_kth_occurrence(m, m);
        sum += p;
    }

    // Output as string
    string ans;
    if (sum == 0) ans = "0";
    while (sum > 0) {
        ans = char('0' + (int)(sum % 10)) + ans;
        sum /= 10;
    }
    cout << ans << "\n";

    return 0;
}
