#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int _; cin >> _;
    int p[] = {2, 3, 5, 7, 11, 13, 17};
    string s = "0123456789";
    ll ans = 0;
    do {
        if (s[0] == '0') continue;
        bool ok = true;
        for (int i = 0; i < 7; i++) {
            int x = (s[i+1]-'0')*100 + (s[i+2]-'0')*10 + (s[i+3]-'0');
            if (x % p[i]) { ok = false; break; }
        }
        if (ok) ans += stoll(s);
    } while (next_permutation(s.begin(), s.end()));
    cout << ans << "\n";
}
