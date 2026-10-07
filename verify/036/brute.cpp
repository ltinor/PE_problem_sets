#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Check decimal palindrome
bool isPalDec(int n) {
    int rev = 0, tmp = n;
    while (tmp > 0) {
        rev = rev * 10 + tmp % 10;
        tmp /= 10;
    }
    return rev == n;
}

// Check binary palindrome
bool isPalBin(int n) {
    if (n == 0) return true;
    int bits[32];
    int len = 0;
    int tmp = n;
    while (tmp > 0) {
        bits[len++] = tmp & 1;
        tmp >>= 1;
    }
    for (int i = 0; i < len / 2; i++) {
        if (bits[i] != bits[len - 1 - i]) return false;
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

        ll total = 0;
        for (int i = 1; i < N && i <= 1000000; i++) {
            if (isPalDec(i) && isPalBin(i)) {
                total += i;
            }
        }
        cout << total << "\n";
    }
    return 0;
}
