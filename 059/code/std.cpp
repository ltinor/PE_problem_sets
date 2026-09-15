#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int N; cin >> N;
    vector<int> c(N);
    for (int i = 0; i < N; i++) cin >> c[i];
    // Try all 3-lowercase keys
    for (char a = 'a'; a <= 'z'; a++)
    for (char b = 'a'; b <= 'z'; b++)
    for (char ck = 'a'; ck <= 'z'; ck++) {
        string key = {a, b, ck};
        string dec;
        bool ok = true;
        int sum = 0;
        for (int i = 0; i < N; i++) {
            char ch = c[i] ^ key[i % 3];
            if (ch < 32 || ch > 126) { ok = false; break; }
            dec += ch;
            sum += (unsigned char)ch;
        }
        if (ok && dec.find(" the ") != string::npos) {
            cout << sum << "\n";
            return 0;
        }
    }
}
