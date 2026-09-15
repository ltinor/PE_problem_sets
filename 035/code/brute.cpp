#include<bits/stdc++.h>
using namespace std;
#define ll long long

bool isPrimeNum(int n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int d = 3; d * d <= n; d += 2) {
        if (n % d == 0) return false;
    }
    return true;
}

bool isCircular(int n) {
    if (!isPrimeNum(n)) return false;
    string s = to_string(n);
    int len = s.size();
    for (int r = 1; r < len; r++) {
        rotate(s.begin(), s.begin() + 1, s.end());
        int rot = stoi(s);
        if (!isPrimeNum(rot)) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;

        int cnt = 0;
        for (int i = 2; i < N && i <= 1000000; i++) {
            if (isCircular(i)) cnt++;
        }
        cout << cnt << "\n";
    }
    return 0;
}
