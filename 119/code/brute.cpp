#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

int digit_sum(ull x) {
    int s = 0;
    while (x) { s += int(x % 10); x /= 10; }
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<ull> nums;
    for (int s = 2; s <= 200; s++) {
        ull p = s;
        for (int e = 2; ; e++) {
            if (p > 18000000000000000000ULL / s) break;
            p *= s;
            if (p < 10) continue;
            if (digit_sum(p) == s) {
                nums.push_back(p);
            }
        }
    }
    sort(nums.begin(), nums.end());

    int T;
    cin >> T;
    while (T--) {
        int K;
        cin >> K;
        cout << nums[K - 1] << "\n";
    }
    return 0;
}
