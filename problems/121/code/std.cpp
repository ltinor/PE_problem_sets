#include <bits/stdc++.h>
using namespace std;
typedef __int128 i128;

// Compute exact probability as fraction num/den
// For each turn i (1-indexed): blue prob = 1/(i+1), red prob = i/(i+1)
// Win if #blue > N/2
// Enumerate all 2^N combinations
pair<i128, i128> calc_prob(int N) {
    i128 total_num = 0, total_den = 1;
    // denominator for all: product of (i+1) for i=1..N
    for (int i = 1; i <= N; i++) total_den *= (i + 1);
    
    // enumerate all subsets (bitmask: bit i=1 means blue on turn i+1)
    for (int mask = 0; mask < (1 << N); mask++) {
        int blue = __builtin_popcount(mask);
        if (blue <= N / 2) continue; // need more blue than red
        // numerator for this combination
        i128 num = 1;
        for (int i = 0; i < N; i++) {
            if (mask & (1 << i)) {
                // blue: factor 1
                // num *= 1 (no change)
            } else {
                // red: factor (i+1) = number of red discs at turn i+1
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
    // prize = floor(1/P) = floor(den/num)
    long long prize = (long long)(den / num);
    cout << prize << "\n";
    return 0;
}
