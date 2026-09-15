#include <bits/stdc++.h>
using namespace std;

// Same segment masks
// segment masks for digits 0-9 
// Bits: 0=top, 1=top-left, 2=top-right, 3=middle, 4=bottom-left, 5=bottom-right, 6=bottom
const int seg[10] = {
    0b1110111, // 0: top, top-left, top-right, bottom-left, bottom-right, bottom
    0b0100100, // 1: top-right, bottom-right
    0b1011101, // 2: top, top-right, middle, bottom-left, bottom
    0b1101101, // 3: top, top-right, middle, bottom-right, bottom
    0b0101011, // 4: top-left, top-right, middle, bottom-right
    0b1101011, // 5: top, top-left, middle, bottom-right, bottom
    0b1111011, // 6: top, top-left, middle, bottom-left, bottom-right, bottom
    0b1100101, // 7: top, top-right, bottom-right, bottom
    0b1111111, // 8: all segments
    0b1101111  // 9: top, top-left, top-right, middle, bottom-right, bottom
};
int seg_cnt[10];

int droot(int n) { return 1 + (n - 1) % 9; }
int pc(int x) { return __builtin_popcount(x); }

vector<int> number_digits(int n) {
    if (n == 0) return {seg[0]};
    vector<int> res;
    while (n > 0) { res.push_back(seg[n % 10]); n /= 10; }
    return res;
}

long long sam_cost(int n) {
    long long cost = 0;
    if (n == 0) return 2LL * seg_cnt[0];
    while (n > 0) { cost += 2LL * seg_cnt[n % 10]; n /= 10; }
    return cost;
}

int max_transition(int a, int b) {
    vector<int> da = number_digits(a);
    vector<int> db = number_digits(b);
    int max_len = max(da.size(), db.size());
    da.resize(max_len, 0);
    db.resize(max_len, 0);
    int cost = 0;
    for (int i = 0; i < max_len; i++)
        cost += pc(da[i] ^ db[i]);
    return cost;
}

pair<long long, long long> compute_costs(int p) {
    vector<int> seq;
    int cur = p;
    while (true) {
        seq.push_back(cur);
        if (cur < 10) break;
        cur = droot(cur);
    }
    long long sam = 0;
    for (int x : seq) sam += sam_cost(x);
    long long max_c = 0;
    max_c += sam_cost(seq[0]) / 2;
    for (int i = 0; i + 1 < (int)seq.size(); i++)
        max_c += max_transition(seq[i], seq[i+1]);
    max_c += sam_cost(seq.back()) / 2;
    return {sam, max_c};
}

bool is_prime_brute(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    for (int i = 0; i < 10; i++) seg_cnt[i] = pc(seg[i]);

    int A, B;
    cin >> A >> B;

    long long total_diff = 0;
    for (int p = A; p <= B; p++) {
        if (is_prime_brute(p)) {
            auto [sam, max_c] = compute_costs(p);
            total_diff += sam - max_c;
        }
    }
    cout << total_diff << "\n";
    return 0;
}
