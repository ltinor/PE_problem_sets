#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Big integer multiplication for brute force
string multiply(string a, string b) {
    int n = a.size(), m = b.size();
    vector<int> res(n + m, 0);
    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            res[i + j + 1] += (a[i] - '0') * (b[j] - '0');
        }
    }
    for (int i = n + m - 1; i > 0; i--) {
        res[i - 1] += res[i] / 10;
        res[i] %= 10;
    }
    string s;
    int i = 0;
    while (i < n + m && res[i] == 0) i++;
    if (i == n + m) return "0";
    for (; i < n + m; i++) s += char('0' + res[i]);
    return s;
}

string power(int base, int exp) {
    string result = "1";
    string b = to_string(base);
    for (int i = 0; i < exp; i++) {
        result = multiply(result, b);
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int A_max, B_max;
        cin >> A_max >> B_max;

        set<string> distinct;
        for (int a = 2; a <= A_max; a++) {
            for (int b = 2; b <= B_max; b++) {
                distinct.insert(power(a, b));
            }
        }
        cout << distinct.size() << "\n";
    }
    return 0;
}
