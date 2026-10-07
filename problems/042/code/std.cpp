#include <bits/stdc++.h>
using namespace std;

bool is_tri(int x) {
    // t_n = n(n+1)/2 = x => n^2 + n - 2x = 0 => n = (-1+sqrt(1+8x))/2
    int d = 1 + 8 * x;
    int s = (int)sqrt(d);
    if (s * s != d) return false;
    return (-1 + s) % 2 == 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int N;
    cin >> N;
    int cnt = 0;
    for (int i = 0; i < N; i++) {
        string w;
        cin >> w;
        int val = 0;
        for (char c : w) val += c - 'A' + 1;
        if (is_tri(val)) cnt++;
    }
    cout << cnt << "\n";
}
