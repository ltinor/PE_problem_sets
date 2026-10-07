#include<bits/stdc++.h>
using namespace std;

// Independent brute implementation of big integer Fibonacci
vector<int> fib_add(const vector<int> &a, const vector<int> &b) {
    vector<int> c;
    int carry = 0;
    int len = max((int)a.size(), (int)b.size());
    for (int i = 0; i < len || carry; i++) {
        if (i < (int)a.size()) carry += a[i];
        if (i < (int)b.size()) carry += b[i];
        c.push_back(carry % 10);
        carry /= 10;
    }
    return c;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int D;
        cin >> D;

        if (D <= 1) {
            cout << "1\n";
            continue;
        }

        vector<int> a = {1}; // F1
        vector<int> b = {1}; // F2
        int index = 2;

        while ((int)b.size() < D) {
            vector<int> c = fib_add(a, b);
            a = b;
            b = c;
            index++;
        }

        cout << index << "\n";
    }
}
