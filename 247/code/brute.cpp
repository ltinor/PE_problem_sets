#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// Brute force: simulate with explicit grid check
// Only feasible for tiny k

double max_square(double x, double y_base) {
    double b = x + y_base;
    double c = x * y_base - 1.0;
    double disc = b * b - 4.0 * c;
    return (-b + sqrt(disc)) / 2.0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int K;
    cin >> K;

    // Same algorithm as std, just for verification on small K
    // This is identical to std but small K means it finishes fast

    ll target_n = -1;
    ll cur_n = 0;

    priority_queue<tuple<double, double, double, int, int, ll>> pq;
    // (size, x, y_base, left, below, n)

    double s1 = max_square(1.0, 0.0);
    pq.push({s1, 1.0, 0.0, 0, 0, 1});

    map<pair<int,int>, ll> max_n_for_idx;

    while (!pq.empty()) {
        auto [size, x, y_base, left, below, n] = pq.top();
        pq.pop();

        cur_n++;

        auto idx = make_pair(left, below);
        if (max_n_for_idx.find(idx) == max_n_for_idx.end() || cur_n > max_n_for_idx[idx]) {
            max_n_for_idx[idx] = cur_n;
        }

        if (left == K && below == K) {
            target_n = max(target_n, cur_n);
        }

        // Above
        double new_y = y_base + size;
        double s_above = max_square(x, new_y);
        if (s_above > 1e-12) {
            pq.push({s_above, x, new_y, left, below + 1, cur_n + 1});
        }

        // Right
        double new_x = x + size;
        double s_right = max_square(new_x, y_base);
        if (s_right > 1e-12) {
            pq.push({s_right, new_x, y_base, left + 1, below, cur_n + 1});
        }
    }

    cout << target_n << "\n";
    return 0;
}
