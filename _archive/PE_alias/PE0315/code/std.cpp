#include <bits/stdc++.h>
using namespace std;

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

int seg_cnt[10]; // popcount of each digit

// digital root of n (>0)
int droot(int n) {
    return 1 + (n - 1) % 9;
}

// popcount
int pc(int x) {
    return __builtin_popcount(x);
}

// segment mask for a number (all digits concatenated, right-aligned)
// Returns a vector of segment masks per digit position
vector<int> number_digits(int n) {
    if (n == 0) return {seg[0]};
    vector<int> res;
    while (n > 0) {
        res.push_back(seg[n % 10]);
        n /= 10;
    }
    return res; // LSB first
}

// Sam cost for displaying number n (on + off)
long long sam_cost(int n) {
    long long cost = 0;
    if (n == 0) return 2LL * seg_cnt[0];
    while (n > 0) {
        cost += 2LL * seg_cnt[n % 10];
        n /= 10;
    }
    return cost;
}

// Max transition cost from number a to b
// = sum over positions of popcount(seg_a ^ seg_b), with right-alignment
int max_transition(int a, int b) {
    vector<int> da = number_digits(a);
    vector<int> db = number_digits(b);
    int max_len = max(da.size(), db.size());
    da.resize(max_len, 0);
    db.resize(max_len, 0);
    int cost = 0;
    for (int i = 0; i < max_len; i++) {
        cost += pc(da[i] ^ db[i]);
    }
    return cost;
}

// compute costs for a prime p
pair<long long, long long> compute_costs(int p) {
    vector<int> seq;
    int cur = p;
    while (true) {
        seq.push_back(cur);
        if (cur < 10) break;
        cur = droot(cur);
    }

    // Sam: 2 * sum of segment counts per number
    long long sam = 0;
    for (int x : seq) {
        sam += sam_cost(x);
    }

    // Max: first ON + sum(transitions) + last OFF
    long long max_c = 0;
    // First number: turn on
    max_c += sam_cost(seq[0]) / 2; // ON only (half of sam_cost)
    // Transitions between numbers
    for (int i = 0; i + 1 < (int)seq.size(); i++) {
        max_c += max_transition(seq[i], seq[i+1]);
    }
    // Last number: turn off
    max_c += sam_cost(seq.back()) / 2; // OFF only

    return {sam, max_c};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 0; i < 10; i++) seg_cnt[i] = pc(seg[i]);

    int A, B;
    cin >> A >> B;

    // sieve primes up to B
    vector<bool> is_prime(B + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= B; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= B; j += i)
                is_prime[j] = false;
        }
    }

    long long total_diff = 0;
    for (int p = A; p <= B; p++) {
        if (is_prime[p]) {
            auto [sam, max_c] = compute_costs(p);
            total_diff += sam - max_c;
        }
    }

    cout << total_diff << "\n";
    return 0;
}
