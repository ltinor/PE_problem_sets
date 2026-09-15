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

    int N;
    cin >> N;

    set<vector<int>> sets;
    vector<int> digits(N);
    iota(digits.begin(), digits.end(), 1);

    do {
        int masks = 1 << (N - 1);
        for (int mask = 0; mask < masks; mask++) {
            vector<int> nums;
            int cur = 0;
            bool ok = true;
            for (int i = 0; i < N; i++) {
                cur = cur * 10 + digits[i];
                if (i == N - 1 || (mask >> i & 1)) {
                    if (!is_prime(cur)) {
                        ok = false;
                        break;
                    }
                    nums.push_back(cur);
                    cur = 0;
                }
            }
            if (ok) {
                sort(nums.begin(), nums.end());
                sets.insert(nums);
            }
        }
    } while (next_permutation(digits.begin(), digits.end()));

    cout << sets.size() << "\n";
    return 0;
}
