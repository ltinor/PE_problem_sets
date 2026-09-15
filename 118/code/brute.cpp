#include <bits/stdc++.h>
using namespace std;

bool is_prime(int x) {
    if (x < 2) return false;
    if (x == 2) return true;
    if (x % 2 == 0) return false;
    for (int i = 3; i * i <= x; i += 2)
        if (x % i == 0) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;

        set<vector<int>> sets;
        vector<int> digits(N);
        for (int i = 0; i < N; i++) digits[i] = i + 1;

        do {
            int totalMasks = 1 << (N - 1);
            for (int mask = 0; mask < totalMasks; mask++) {
                vector<int> parts;
                int cur = 0;
                bool valid = true;
                for (int i = 0; i < N; i++) {
                    cur = cur * 10 + digits[i];
                    if (i == N - 1 || ((mask >> i) & 1)) {
                        if (!is_prime(cur)) {
                            valid = false;
                            break;
                        }
                        parts.push_back(cur);
                        cur = 0;
                    }
                }
                if (valid) {
                    sort(parts.begin(), parts.end());
                    sets.insert(parts);
                }
            }
        } while (next_permutation(digits.begin(), digits.end()));

        cout << sets.size() << "\n";
    }
    return 0;
}
