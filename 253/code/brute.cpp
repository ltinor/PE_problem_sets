#include <bits/stdc++.h>
using namespace std;

int max_segments(const vector<int>& perm) {
    int N = (int)perm.size();
    vector<bool> placed(N + 2, false);
    int seg = 0, max_seg = 0;

    for (int i = 0; i < N; i++) {
        int v = perm[i];
        bool left = placed[v - 1];
        bool right = placed[v + 1];
        if (!left && !right) seg++;
        else if (left && right) seg--;
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

    // Brute force: enumerate all permutations for small N
    vector<int> perm(N);
    iota(perm.begin(), perm.end(), 1);

    long long total_max = 0;
    long long count = 0;
    do {
        total_max += max_segments(perm);
        count++;
    } while (next_permutation(perm.begin(), perm.end()));

    double avg = (double)total_max / count;
    cout << fixed << setprecision(6) << avg << "\n";
    return 0;
}
