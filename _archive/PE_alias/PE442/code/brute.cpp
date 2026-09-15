#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

// PE442 brute: check each number for eleven-free property (very small n only)

bool is_eleven_free(ll x) {
    string s = to_string(x);
    // Powers of 11: 11, 121, 1331, 14641, 161051, 1771561, ...
    vector<string> bad = {"11", "121", "1331", "14641", "161051", "1771561", "19487171"};
    for (const string& p : bad) {
        if (s.find(p) != string::npos) return false;
    }
    return true;
}

ull E_brute(ull n) {
    ull cnt = 0;
    for (ull x = 1; ; x++) {
        if (is_eleven_free(x)) {
            cnt++;
            if (cnt == n) return x;
        }
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    ull n; cin >> n;
    cout << E_brute(n) << "\n";
}
