#include <bits/stdc++.h>
using namespace std;

// Simulate one permutation and return max segments
int max_segments(const vector<int>& perm) {
    int N = (int)perm.size();
    vector<bool> placed(N + 2, false); // 1-indexed with sentinels
    int seg = 0, max_seg = 0;

    for (int i = 0; i < N; i++) {
        int v = perm[i];
        bool left = placed[v - 1];
        bool right = placed[v + 1];

        if (!left && !right) seg++;
        else if (left && right) seg--;
        // else: seg unchanged (extending)

        placed[v] = true;
        max_seg = max(max_seg, seg);
    }
    return max_seg;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    // Monte Carlo simulation
    const int SAMPLES = (N <= 20) ? 5000000 : 2000000;
    vector<int> perm(N);
    iota(perm.begin(), perm.end(), 1);

    long long total_max = 0;
    // Use deterministic seed for reproducibility with gen
    mt19937 rng(42);

    for (int s = 0; s < SAMPLES; s++) {
        shuffle(perm.begin(), perm.end(), rng);
        total_max += max_segments(perm);
    }

    double avg = (double)total_max / SAMPLES;
    cout << fixed << setprecision(6) << avg << "\n";
    return 0;
}
