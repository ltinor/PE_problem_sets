#include <bits/stdc++.h>
using namespace std;

vector<int> mul(const vector<int>& a, int b) {
    vector<int> res;
    int carry = 0;
    for (int i = 0; i < (int)a.size() || carry; i++) {
        if (i < (int)a.size()) carry += a[i] * b;
        res.push_back(carry % 10);
        carry /= 10;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int a, b;
        cin >> a >> b;
        vector<int> digs = {1};
        for (int i = 0; i < b; i++) digs = mul(digs, a);
        int sum = 0;
        for (int d : digs) sum += d;
        cout << sum << "\n";
    }
}
