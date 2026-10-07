#include<bits/stdc++.h>
using namespace std;
#define ll long long

struct Dart {
    int score;
    int id;  // unique id for ordering
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Build all non-finishing dart types
    vector<Dart> all_darts;
    int id = 0;
    // Singles: S1-S20 (1-20), S25 (25)
    for (int i = 1; i <= 20; i++) all_darts.push_back({i, id++});
    all_darts.push_back({25, id++});  // S25
    // Doubles: D1-D20 (2,4,...,40), D25 (50)
    for (int i = 1; i <= 20; i++) all_darts.push_back({2*i, id++});
    all_darts.push_back({50, id++});  // D25
    // Trebles: T1-T20 (3,6,...,60)
    for (int i = 1; i <= 20; i++) all_darts.push_back({3*i, id++});

    // Build all finishing doubles
    vector<Dart> doubles;
    for (int i = 1; i <= 20; i++) doubles.push_back({2*i, 0});
    doubles.push_back({50, 0});  // D25

    int S;
    cin >> S;

    // Count checkouts for each score
    const int MAX_SCORE = 170;
    vector<ll> cnt(MAX_SCORE + 1, 0);

    // 1-dart checkouts
    for (auto& d : doubles) {
        if (d.score <= MAX_SCORE) cnt[d.score]++;
    }

    // 2-dart checkouts: a + d
    for (auto& a : all_darts) {
        for (auto& d : doubles) {
            int sc = a.score + d.score;
            if (sc <= MAX_SCORE) cnt[sc]++;
        }
    }

    // 3-dart checkouts: a + b + d (a.id <= b.id for dedup)
    for (auto& d : doubles) {
        for (size_t i = 0; i < all_darts.size(); i++) {
            for (size_t j = i; j < all_darts.size(); j++) {
                int sc = all_darts[i].score + all_darts[j].score + d.score;
                if (sc <= MAX_SCORE) cnt[sc]++;
            }
        }
    }

    // Sum for all scores < S
    ll ans = 0;
    for (int sc = 2; sc < S; sc++) {
        ans += cnt[sc];
    }

    cout << ans << "\n";
    return 0;
}
