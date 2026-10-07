#include<bits/stdc++.h>
using namespace std;

// Brute force: enumerate all permutations (N ≤ 8)

double calc_len(const vector<int>& perm, const vector<int>& r, int R,
                const vector<vector<double>>& h) {
    double len = r[perm[0]];
    for(int i = 0; i + 1 < (int)perm.size(); i++) {
        len += h[perm[i]][perm[i+1]];
    }
    len += r[perm.back()];
    return len;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, R;
    cin >> N >> R;

    vector<int> r(N);
    for(int i = 0; i < N; i++) r[i] = 30 + i;

    vector<vector<double>> h(N, vector<double>(N, 0));
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(i == j) continue;
            double sum_r = r[i] + r[j];
            double horiz = 2.0 * R - r[i] - r[j];
            double val = sum_r * sum_r - horiz * horiz;
            if(val <= 0) h[i][j] = 1e18;
            else h[i][j] = sqrt(val);
        }
    }

    vector<int> perm(N);
    iota(perm.begin(), perm.end(), 0);
    double best = 1e18;
    do {
        best = min(best, calc_len(perm, r, R, h));
    } while(next_permutation(perm.begin(), perm.end()));

    long long result = (long long)round(best * 1000.0);
    cout << result << "\n";
    return 0;
}
