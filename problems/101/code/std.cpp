#include <bits/stdc++.h>
using namespace std;
using i128 = __int128;

// Binomial coefficient C(n, k) for n <= 10
i128 C[15][15];

void init_comb() {
    for (int i = 0; i <= 12; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++)
            C[i][j] = C[i-1][j-1] + C[i-1][j];
    }
}

// u_j = sum_{t=0}^{N} (-1)^t * j^t
i128 compute_u(int j, int N) {
    i128 val = 0;
    i128 p = 1; // j^0 = 1
    for (int t = 0; t <= N; t++) {
        if (t % 2 == 0) val += p;
        else val -= p;
        p *= j;
    }
    return val;
}

// FIT for BOP with k points: sum_{j=1}^{k} (-1)^{k-j} * C(k, j-1) * u_j
i128 compute_fit(int k, int N) {
    i128 sum = 0;
    for (int j = 1; j <= k; j++) {
        i128 uj = compute_u(j, N);
        i128 term = C[k][j-1] * uj;
        if ((k - j) % 2 == 1) sum -= term;
        else sum += term;
    }
    return sum;
}

// Print __int128
void print_i128(i128 x) {
    if (x == 0) { cout << "0"; return; }
    if (x < 0) { cout << "-"; x = -x; }
    string s;
    while (x > 0) { s += char('0' + (x % 10)); x /= 10; }
    reverse(s.begin(), s.end());
    cout << s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init_comb();

    int N;
    cin >> N;

    i128 ans = 0;
    for (int k = 1; k <= N; k++) {
        ans += compute_fit(k, N);
    }

    print_i128(ans);
    cout << "\n";
    return 0;
}
