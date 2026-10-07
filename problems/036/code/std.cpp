#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Check if decimal string is palindrome
bool isPalDec(int n) {
    string s = to_string(n);
    int L = 0, R = s.size() - 1;
    while (L < R) {
        if (s[L] != s[R]) return false;
        L++; R--;
    }
    return true;
}

// Check if binary representation is palindrome
bool isPalBin(int n) {
    if (n == 0) return true;
    // Build binary string without leading zeros
    string bin;
    int tmp = n;
    while (tmp > 0) {
        bin += (tmp & 1) ? '1' : '0';
        tmp >>= 1;
    }
    int L = 0, R = bin.size() - 1;
    while (L < R) {
        if (bin[L] != bin[R]) return false;
        L++; R--;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int MAXN = 1000000;
    // Precompute prefix sums
    static ll pre[MAXN + 1];
    static bool done = false;
    if (!done) {
        done = true;
        pre[0] = 0;
        for (int i = 1; i <= MAXN; i++) {
            if (isPalDec(i) && isPalBin(i)) {
                pre[i] = pre[i - 1] + i;
            } else {
                pre[i] = pre[i - 1];
            }
        }
    }

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        if (N > MAXN) N = MAXN;
        if (N <= 0) cout << "0\n";
        else cout << pre[N - 1] << "\n";
    }
    return 0;
}
