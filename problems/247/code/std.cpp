#include <bits/stdc++.h>
using namespace std;
using ll = long long;

double max_square(double x, double y_base) {
    double b = x + y_base;
    double c = x * y_base - 1.0;
    double disc = b * b - 4.0 * c;
    if (disc < 0) return 0;
    return (-b + sqrt(disc)) / 2.0;
}

struct State {
    double size;
    double x;
    double y_base;
    int left, below;

    bool operator<(const State& other) const {
        return size < other.size; // max-heap
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    cin >> K;

    ll target_n = -1;
    ll cur_n = 0;

    priority_queue<State> pq;
    map<pair<int,int>, ll> max_n_for_idx;

    double s1 = max_square(1.0, 0.0);
    if (s1 > 0) pq.push({s1, 1.0, 0.0, 0, 0});

    // Process squares in size order until we've found answer or exhausted
    // For K=3, answer is 782252; process 2M squares for safety
    const ll MAX_STEPS = 2000000LL;
    ll last_found_at = -1;

    while (!pq.empty() && cur_n < MAX_STEPS) {
        State cur = pq.top();
        pq.pop();
        cur_n++;

        auto idx = make_pair(cur.left, cur.below);
        auto it = max_n_for_idx.find(idx);
        if (it == max_n_for_idx.end() || cur_n > it->second) {
            max_n_for_idx[idx] = cur_n;
        }

        if (cur.left == K && cur.below == K) {
            target_n = max(target_n, cur_n);
            last_found_at = cur_n;
        }

        // Stop early if we've gone far past the last (K,K) without finding new ones
        if (last_found_at > 0 && cur_n > last_found_at * 3) break;

        // Generate child: above (same x, higher y_base)
        double new_y = cur.y_base + cur.size;
        double s_above = max_square(cur.x, new_y);
        if (s_above > 1e-15) {
            pq.push({s_above, cur.x, new_y, cur.left, cur.below + 1});
        }

        // Generate child: right (higher x, same y_base)
        double new_x = cur.x + cur.size;
        double s_right = max_square(new_x, cur.y_base);
        if (s_right > 1e-15) {
            pq.push({s_right, new_x, cur.y_base, cur.left + 1, cur.below});
        }
    }

    cout << target_n << "\n";
    return 0;
}
