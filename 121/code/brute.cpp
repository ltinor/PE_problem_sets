#include <bits/stdc++.h>
using namespace std;
typedef __int128 i128;

// Brute force: same as std — exact fraction computation
pair<i128, i128> calc_prob(int N) {
    i128 total_num = 0, total_den = 1;
    for (int i = 1; i <= N; i++) total_den *= (i + 1);
    
    for (int mask = 0; mask < (1 << N); mask++) {
        int blue = __builtin_popcount(mask);
        if (blue <= N / 2) continue;
        i128 num = 1;
        for (int i = 0; i < N; i++) {
            if (!(mask & (1 << i))) {
                num *= (i + 1);
            }
        }
        total_num += num;
    }
    return {total_num, total_den};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    
    auto [num, den] = calc_prob(N);
    long long prize = (long long)(den / num);
    cout << prize << "\n";
    return 0;
}
