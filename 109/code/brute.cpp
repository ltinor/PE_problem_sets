#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Brute force: same enumeration but using direct nested loops
// for independence from std's data structures.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Scores for all dart types
    vector<int> singles, doubles, trebles;

    for (int i = 1; i <= 20; i++) singles.push_back(i);
    singles.push_back(25);  // outer bull

    for (int i = 1; i <= 20; i++) doubles.push_back(2 * i);
    doubles.push_back(50);  // bullseye

    for (int i = 1; i <= 20; i++) trebles.push_back(3 * i);

    // All non-finishing dart scores (for first/second darts)
    vector<int> all_scores;
    for (int s : singles) all_scores.push_back(s);
    for (int s : doubles) all_scores.push_back(s);
    for (int s : trebles) all_scores.push_back(s);
    sort(all_scores.begin(), all_scores.end());

    int S;
    cin >> S;

    const int MAX_SCORE = 170;
    vector<ll> cnt(MAX_SCORE + 1, 0);

    // 1-dart
    for (int d : doubles) {
        if (d <= MAX_SCORE) cnt[d]++;
    }

    // 2-dart
    for (int a : all_scores) {
        for (int d : doubles) {
            int sc = a + d;
            if (sc <= MAX_SCORE) cnt[sc]++;
        }
    }

    // 3-dart: two non-finishing (unordered) + finishing double
    int m = all_scores.size();
    for (int d : doubles) {
        for (int i = 0; i < m; i++) {
            for (int j = i; j < m; j++) {
                int sc = all_scores[i] + all_scores[j] + d;
                if (sc <= MAX_SCORE) cnt[sc]++;
            }
        }
    }

    ll ans = 0;
    for (int sc = 2; sc < S; sc++) {
        ans += cnt[sc];
    }

    cout << ans << "\n";
    return 0;
}
