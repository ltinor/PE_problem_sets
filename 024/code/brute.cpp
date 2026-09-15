#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N; long long K;
        cin >> N >> K;

        vector<int> perm(N);
        for (int i = 0; i < N; i++) perm[i] = i;

        // next_permutation K-1 times (K is 1-indexed)
        for (long long t = 1; t < K; t++) {
            next_permutation(perm.begin(), perm.end());
        }

        for (int i = 0; i < N; i++) cout << perm[i];
        cout << "\n";
    }
}
