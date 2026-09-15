#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// Brute force: enumerate all binary strings of length n
// and check palindrome-like property
bool is_palindrome_like(const string& s) {
    int n = s.size();
    // Check if s can be made palindrome by some allowed transformations
    for (int i = 0; i < n/2; i++) {
        if (s[i] != s[n-1-i]) return false;
    }
    return true;
}

int main() {
    int n; cin >> n;
    ll cnt = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        string s;
        for (int i = 0; i < n; i++)
            s += ((mask >> i) & 1) ? '1' : '0';
        if (is_palindrome_like(s)) cnt++;
    }
    cout << cnt << "\n";
}
