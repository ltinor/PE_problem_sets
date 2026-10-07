#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int K; cin >> K;

    // Generate cubes, sort digits to form a key, group by key
    map<string, vector<ull>> groups;
    for (ull n = 1; ; n++) {
        ull cube = n * n * n;
        string s = to_string(cube);
        sort(s.begin(), s.end());
        groups[s].push_back(cube);
        // Once we have a group with K entries, and the cube has more digits
        // than any key in a smaller-digit group, we can stop
        // But simplest: just generate enough
        if (groups[s].size() == K) {
            // Check if we've found the answer: the smallest cube in a group of size K
            // We need to check all groups to ensure we find the global minimum
        }
        // Generate up to a reasonable limit
        if (n > 10000) break;
    }

    ull best = ULLONG_MAX;
    for (auto& p : groups) {
        if (p.second.size() == (size_t)K) {
            best = min(best, p.second[0]);
        }
    }

    // If we didn't find it, we need more digits. But for K <= 5, 10000 is enough
    // Actually for K=5 we need cubes up to 12 digits. Let's use 100000 just to be safe.
    // Re-generate with larger bound if needed
    if (best == ULLONG_MAX) {
        groups.clear();
        for (ull n = 1; n <= 100000; n++) {
            ull cube = n * n * n;
            string s = to_string(cube);
            sort(s.begin(), s.end());
            groups[s].push_back(cube);
        }
        for (auto& p : groups) {
            if (p.second.size() == (size_t)K) {
                best = min(best, p.second[0]);
            }
        }
    }

    cout << best << "\n";
}
