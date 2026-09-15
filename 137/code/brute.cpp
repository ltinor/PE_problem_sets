#include<bits/stdc++.h>
using namespace std;

#define ll long long

// Brute force: same recurrence as std for golden nuggets
// N_1=2, N_2=15, N_k = 7*N_{k-1} - N_{k-2} + 1

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    cin >> K;

    if (K == 1) { cout << "2\n"; return 0; }
    if (K == 2) { cout << "15\n"; return 0; }

    ll a = 2, b = 15, c;
    for (int i = 3; i <= K; i++) {
        c = 7 * b - a + 1;
        a = b;
        b = c;
    }

    cout << b << "\n";
    return 0;
}
