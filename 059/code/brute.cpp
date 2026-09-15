#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int N; cin >> N;
    vector<int> c(N);
    for (int i = 0; i < N; i++) cin >> c[i];
    int best = 0;
    for (char a = 'a'; a <= 'z'; a++)
    for (char b = 'a'; b <= 'z'; b++)
    for (char ck = 'a'; ck <= 'z'; ck++) {
        string key = {a, b, ck};
        int sum = 0; bool ok = true;
        for (int i = 0; i < N; i++) {
            char ch = c[i] ^ key[i % 3];
            if (ch < 32 || ch > 126) { ok = false; break; }
            sum += (unsigned char)ch;
        }
        if (ok) {
            // Simple heuristic: count spaces and 'e'
            int sp = 0, ec = 0;
            for (int i = 0; i < N; i++) {
                char ch = c[i] ^ key[i % 3];
                if (ch == ' ') sp++;
                if (ch == 'e' || ch == 'E') ec++;
            }
            if (sp > N/10 && ec > N/20) { best = sum; break; }
        }
    }
    cout << best << "\n";
}
