#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Same approach as std but simpler, for verification
ll find_kth_occurrence(ll m, ll k) {
    string ms = to_string(m);
    int L = ms.length();

    string window;
    ll pos = 1;
    ll occ = 0;

    for (ll num = 1; ; num++) {
        string ns = to_string(num);
        int nlen = ns.length();

        // Within current number
        for (int i = 0; i + L <= nlen; i++) {
            if (ns.substr(i, L) == ms) {
                occ++;
                if (occ == k) return pos + i;
            }
        }

        // Cross boundary
        string combined = window + ns;
        int wlen = window.length();
        for (int i = 0; i < wlen; i++) {
            if (i + L <= (int)combined.length()) {
                if (combined.substr(i, L) == ms) {
                    occ++;
                    if (occ == k) return pos - wlen + i;
                }
            }
        }

        // Update window
        if (nlen >= L - 1) {
            window = ns.substr(nlen - (L - 1));
        } else {
            window = window + ns;
            if ((int)window.length() > L - 1)
                window = window.substr(window.length() - (L - 1));
        }

        pos += nlen;
        if (pos > 100000000) break;
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll K;
    cin >> K;

    ll sum = 0;
    for (ll k = 1; k <= K; k++) {
        ll m = 1;
        for (ll i = 0; i < k; i++) m *= 3;
        sum += find_kth_occurrence(m, m);
    }

    cout << sum << "\n";
    return 0;
}
