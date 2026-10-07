#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Check if s is a valid square (no leading zero for multi-digit)
bool is_square(ll x) {
    ll r = (ll)sqrt((long double)x);
    while (r * r < x) r++;
    while (r * r > x) r--;
    return r * r == x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<string> words(N);
    for (int i = 0; i < N; i++) cin >> words[i];

    // Group by anagram pattern (sorted chars)
    map<string, vector<string>> groups;
    for (const string& w : words) {
        string key = w;
        sort(key.begin(), key.end());
        groups[key].push_back(w);
    }

    ll best = 0;

    for (auto& [key, group] : groups) {
        if (group.size() < 2) continue;
        int L = group[0].size();

        // For each pair in group
        int sz = group.size();
        for (int i = 0; i < sz; i++) {
            for (int j = i + 1; j < sz; j++) {
                const string& w1 = group[i];
                const string& w2 = group[j];

                // Build position mapping: char -> positions in w1
                // and check it maps correctly to w2
                // Actually: we need a bijection from distinct letters to digits
                // Get distinct letters in w1
                vector<char> letters;
                {
                    bool seen[26] = {};
                    for (char c : w1) {
                        if (!seen[c - 'A']) {
                            seen[c - 'A'] = true;
                            letters.push_back(c);
                        }
                    }
                }
                int D = letters.size();
                if (D > 10) continue; // too many distinct letters

                // Map letter to index
                int char_to_idx[26];
                for (int k = 0; k < D; k++) char_to_idx[letters[k] - 'A'] = k;

                // Precompute digit positions for w1 and w2
                vector<int> pos1(L), pos2(L);
                for (int k = 0; k < L; k++) {
                    pos1[k] = char_to_idx[w1[k] - 'A'];
                }
                // For w2, we need the same mapping
                // Build mapping from w1 chars to w2 positions
                vector<int> pos2_from_idx(D, -1);
                for (int k = 0; k < L; k++) {
                    int idx = char_to_idx[w2[k] - 'A'];
                    pos2[k] = idx;
                }

                // Generate all D-digit permutations (0-9 choose D, then permute)
                // But simpler: iterate over squares of length L
                ll lo = 1;
                for (int k = 1; k < L; k++) lo *= 10;
                ll hi = lo * 10 - 1;

                ll sq_lo = (ll)ceil(sqrt((long double)lo));
                ll sq_hi = (ll)floor(sqrt((long double)hi));

                // Also handle 1-digit case
                if (L == 1) {
                    lo = 1; hi = 9;
                    sq_lo = 1; sq_hi = 3;
                }

                for (ll r = sq_lo; r <= sq_hi; r++) {
                    ll s1 = r * r;
                    string s1_str = to_string(s1);
                    if ((int)s1_str.size() != L) continue;

                    // Map digits to letters for w1
                    int letter_to_digit[26];
                    memset(letter_to_digit, -1, sizeof(letter_to_digit));
                    bool digit_used[10] = {};
                    bool ok = true;

                    for (int k = 0; k < L; k++) {
                        int ci = w1[k] - 'A';
                        int d = s1_str[k] - '0';
                        if (letter_to_digit[ci] == -1) {
                            if (digit_used[d]) { ok = false; break; }
                            letter_to_digit[ci] = d;
                            digit_used[d] = true;
                        } else if (letter_to_digit[ci] != d) {
                            ok = false; break;
                        }
                    }
                    if (!ok) continue;

                    // Check no leading zero in w2
                    if (letter_to_digit[w2[0] - 'A'] == 0) continue;

                    // Build number for w2
                    ll s2 = 0;
                    for (int k = 0; k < L; k++) {
                        int d = letter_to_digit[w2[k] - 'A'];
                        s2 = s2 * 10 + d;
                    }

                    if (is_square(s2)) {
                        best = max(best, max(s1, s2));
                    }
                }
            }
        }
    }

    cout << best << "\n";
    return 0;
}
