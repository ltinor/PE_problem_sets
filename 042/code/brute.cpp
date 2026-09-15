#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N; cin >> N;
    int cnt = 0;
    set<int> tri;
    for (int n = 1; n * (n + 1) / 2 <= 26 * 20; n++)
        tri.insert(n * (n + 1) / 2);
    for (int i = 0; i < N; i++) {
        string w; cin >> w;
        int val = 0;
        for (char c : w) val += c - 'A' + 1;
        if (tri.count(val)) cnt++;
    }
    cout << cnt << "\n";
}
