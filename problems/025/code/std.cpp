#include<bits/stdc++.h>
using namespace std;

// Big integer represented as vector of digits (least significant first)
using BigInt = vector<int>;

BigInt add(const BigInt &a, const BigInt &b) {
    BigInt res;
    int carry = 0;
    int n = max(a.size(), b.size());
    for (int i = 0; i < n || carry; i++) {
        int sum = carry;
        if (i < a.size()) sum += a[i];
        if (i < b.size()) sum += b[i];
        res.push_back(sum % 10);
        carry = sum / 10;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int D;
        cin >> D;

        if (D == 1) {
            cout << "1\n";
            continue;
        }

        BigInt f1 = {1}; // F1
        BigInt f2 = {1}; // F2
        int idx = 2;     // current index of f2

        while ((int)f2.size() < D) {
            BigInt f3 = add(f1, f2);
            f1 = f2;
            f2 = f3;
            idx++;
        }

        cout << idx << "\n";
    }
}
