#include <bits/stdc++.h>
using namespace std;

vector<int> add(const vector<int>& a, const vector<int>& b) {
    vector<int> res;
    int carry = 0;
    for (size_t i = 0; i < max(a.size(), b.size()) || carry; i++) {
        if (i < a.size()) carry += a[i];
        if (i < b.size()) carry += b[i];
        res.push_back(carry % 10);
        carry /= 10;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int N;
    while (cin >> N) {
        vector<int> n = {1}, d = {1};
        int ans = 0;
        for (int i = 0; i < N; i++) {
            auto nn = add(n, add(d, d));
            auto nd = add(n, d);
            n = nn; d = nd;
            if (n.size() > d.size()) ans++;
        }
        cout << ans << "\n";
    }
}
