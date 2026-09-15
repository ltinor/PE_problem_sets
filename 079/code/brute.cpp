#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<string> attempts(N);
    set<char> chars;
    for (int i = 0; i < N; i++) {
        cin >> attempts[i];
        for (char c : attempts[i]) chars.insert(c);
    }

    // Brute force: try all permutations of the unique characters
    string digits(chars.begin(), chars.end());
    sort(digits.begin(), digits.end());

    string best;
    int best_len = 100;

    // Try all permutations
    do {
        // Check if this order satisfies all constraints
        bool ok = true;
        for (string &s : attempts) {
            int pos0 = digits.find(s[0]);
            int pos1 = digits.find(s[1]);
            int pos2 = digits.find(s[2]);
            if (!(pos0 < pos1 && pos1 < pos2)) {
                ok = false;
                break;
            }
        }
        if (ok) {
            int len = digits.size();
            if (len < best_len) {
                best_len = len;
                best = digits;
            } else if (len == best_len && digits < best) {
                best = digits;
            }
        }
    } while (next_permutation(digits.begin(), digits.end()));

    cout << best << "\n";

    return 0;
}
