#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Fibonacci words: F_1 = A, F_2 = B, F_k = F_{k-2} || F_{k-1}
// D(A,B,n) = nth digit of first term with >= n digits
// Input: A, B (on separate lines), then n
// Output: D(A,B,n) as a single digit

char fibonacci_digit(const string& A, const string& B, ll n) {
    // Lengths: L_1 = |A|, L_2 = |B|, L_k = L_{k-2} + L_{k-1}
    vector<ll> lens;
    lens.push_back((ll)A.size());
    lens.push_back((ll)B.size());

    // Build lengths until >= n
    while (lens.back() < n) {
        int sz = lens.size();
        lens.push_back(lens[sz-2] + lens[sz-1]);
    }

    // Now trace back
    int idx = (int)lens.size() - 1;
    ll pos = n; // 1-indexed

    while (idx > 1) {
        ll left_len = lens[idx - 2];
        if (pos <= left_len) {
            idx -= 2;
        } else {
            pos -= left_len;
            idx -= 1;
        }
    }

    if (idx == 0) {
        return A[pos - 1];
    } else {
        return B[pos - 1];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string A, B;
    getline(cin, A);
    getline(cin, B);

    ll n;
    cin >> n;

    cout << fibonacci_digit(A, B, n) << "\n";
    return 0;
}
