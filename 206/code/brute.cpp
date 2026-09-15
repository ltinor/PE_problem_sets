#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 206: Brute force for small patterns
// Enumerate n from lower bound, check n^2 against pattern

bool matches(const string& s, const string& pattern) {
    int len = s.size();
    if (len != (int)pattern.size()) return false;
    for (int i = 0; i < len; i++) {
        if (pattern[i] == '_') continue;
        if (s[i] != pattern[i]) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string pattern;
    cin >> pattern;

    int L = pattern.size();
    ll lo = (ll)ceil(sqrt(pow(10, L - 1) - 0.5));
    ll hi = (ll)floor(sqrt(pow(10, L) - 1.5));

    int step = 1;
    if (pattern.back() == '0') {
        step = 10;
        while (lo % 10 != 0) lo++;
    }

    for (ll n = lo; n <= hi && n <= lo + 100000000; n += step) {
        ll sq = n * n; // For small n, 64-bit is enough
        if (matches(to_string(sq), pattern)) {
            cout << n << "\n";
            return 0;
        }
    }

    cout << "0\n";
    return 0;
}
