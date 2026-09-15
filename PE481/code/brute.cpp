#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

// Brute force: full DP for small N
ld brute_game(int N) {
    int M = (N + 1) / 2;
    vector<vector<ld>> V(M + 1, vector<ld>(M + 1, 0.0L));
    for (int a = 0; a <= M; a++) {
        for (int b = 0; b <= M; b++) {
            if (a == 0 && b == 0) continue;
            if (a == 0) { V[a][b] = 1.0L; continue; }
            if (b == 0) { V[a][b] = 0.0L; continue; }
            V[a][b] = 0.5L * V[a-1][b] + 0.5L * V[a][b-1];
        }
    }
    return V[M][M] * N;
}

int main() {
    cout << fixed << setprecision(8);
    int N; cin >> N;
    cout << brute_game(N) << "\n";
}
