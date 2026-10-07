#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int K; cin >> K;

    map<string, vector<ull>> groups;
    // Generate cubes up to a large enough bound
    for (ull n = 1; n <= 100000; n++) {
        ull cube = n * n * n;
        string s = to_string(cube);
        sort(s.begin(), s.end());
        groups[s].push_back(cube);
    }

    ull best = ULLONG_MAX;
    for (auto& p : groups) {
        if (p.second.size() == (size_t)K) {
            best = min(best, p.second[0]);
        }
    }

    cout << best << "\n";
}
