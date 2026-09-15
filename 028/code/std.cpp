#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        ll N;
        cin >> N;

        // N is odd, N >= 1
        // Sum of diagonals of N×N spiral
        // Formula: for odd N, sum = (4*N^3 + 3*N^2 + 8*N - 9) / 6
        // Derivation:
        //   Layer k (odd, k>=3): corners = k², k²-(k-1), k²-2(k-1), k²-3(k-1)
        //   Sum of 4 corners = 4k² - 6(k-1)
        //   Total = 1 + sum_{odd k from 3 to N} [4k² - 6k + 6]
        //   Let m = (N-1)/2, then k = 2j+1, j=1..m
        //   = 16*sum(j²) + 4*sum(j) + 4m + 1
        //   = (4N³ + 3N² + 8N - 9) / 6

        if (N == 1) {
            cout << "1\n";
        } else {
            // use 128-bit to avoid overflow for N up to 1e9
            __int128 N3 = (__int128)N * N * N;
            __int128 N2 = (__int128)N * N;
            __int128 ans = (4 * N3 + 3 * N2 + 8 * N - 9) / 6;
            // Print __int128
            string s;
            if (ans == 0) s = "0";
            while (ans > 0) {
                s += char('0' + (ans % 10));
                ans /= 10;
            }
            reverse(s.begin(), s.end());
            cout << s << "\n";
        }
    }
    return 0;
}
