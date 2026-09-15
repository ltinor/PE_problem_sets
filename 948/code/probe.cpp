#include <bits/stdc++.h>
using namespace std;

// compute A(0,n-1), B(0,n-1) for a word encoded as bitmask.
// bit i (0=leftmost) = 1 means 'R', 0 means 'L'.
// Return 1 if (A==LeftWins && B==RightWins), else 0.
int wins(int mask, int n) {
    // A[i][j], B[i][j] using bool
    // We'll store as vector of bitsets? Simpler: use 2D arrays of char.
    // For n up to 25, n^2 = 625 per word. Fine.
    static vector<vector<char>> A, B;
    A.assign(n, vector<char>(n, 0));
    B.assign(n, vector<char>(n, 0));
    for (int i = 0; i < n; i++) {
        // leftmost is bit (n-1)
        int bit = (mask >> (n - 1 - i)) & 1; // 0 = L, 1 = R
        A[i][i] = B[i][i] = (bit == 0) ? 1 : 0; // Left wins if letter is L
    }
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;
            A[i][j] = A[i+1][j] || B[i+1][j];
            B[i][j] = A[i][j-1] && B[i][j-1];
        }
    }
    // Left-first: A[0][n-1]==1 means Left wins.
    // Right-first: B[0][n-1]==0 means Right wins.
    return (A[0][n-1] == 1 && B[0][n-1] == 0) ? 1 : 0;
}

long long F(int n) {
    long long cnt = 0;
    int total = 1 << n;
    for (int mask = 0; mask < total; mask++) {
        cnt += wins(mask, n);
    }
    return cnt;
}

int main() {
    int nmax;
    cin >> nmax;
    for (int n = 1; n <= nmax; n++) {
        cout << "F(" << n << ") = " << F(n) << "\n";
        cout.flush();
    }
    return 0;
}
