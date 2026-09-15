#include <bits/stdc++.h>
using namespace std;

// Big integer: vector<int> digits, least significant first
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
    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        vector<int> num = {1}, den = {1}; // 1/1
        // To get next: num' = num + 2*den, den' = num + den
        // But actual sequence: 3/2, 7/5, 17/12, 41/29...
        // Better: num=num+2*den, den=num+den-alt
        // Simpler: iterate the recurrence: n_k = n_{k-1} + 2*d_{k-1}, d_k = n_{k-1} + d_{k-1}
        int cnt = 0;
        for (int i = 1; i <= N; i++) {
            vector<int> new_num = add(num, add(den, den));
            vector<int> new_den = add(num, den);
            num = new_num; den = new_den;
            if (num.size() > den.size()) cnt++;
        }
        cout << cnt << "\n";
    }
}
