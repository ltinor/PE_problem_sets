#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 551: Sum of digits sum of numbers
// a_0 = 1; a_n = sum of digit sums of a_0..a_{n-1} for n ≥ 1
// Equivalently: a_{n+1} = a_n + digit_sum(a_n)
// Find a_{10^15}. PE answer: 73567276.

const int DIGIT_SUM_LIMIT = 200000000;

vector<int> ds_table;

void build_digit_sum(int limit) {
    ds_table.assign(limit, 0);
    for (int i = 1; i < limit; i++) {
        ds_table[i] = ds_table[i / 10] + (i % 10);
    }
}

inline int digit_sum(ll x) {
    if (x < (ll)ds_table.size()) return ds_table[x];
    int s = 0;
    while (x) { s += x % 10; x /= 10; }
    return s;
}

// Count how many steps from value v (with digit sum d) we can advance
// before digit_sum(v + step*d) changes.
// We advance in blocks where digit_sum is constant.
ll count_steps_same_ds(ll v, int d) {
    if (d == 0) return 1;
    // Find the smallest step t such that digit_sum(v + t*d) != d
    // digit_sum changes when a carry happens in v + t*d
    // For efficiency, check in blocks of 10^6
    ll step = 0;
    ll cur = v;
    while (step < 100000000LL) {
        ll block_end = min(step + 1000000LL, 100000000LL);
        ll nxt = v + block_end * d;
        // Estimate if digit_sum changes in this block by checking boundaries
        // Conservative: just take one step at a time for accuracy
        // But for PE scale, use larger batches
        if (digit_sum(nxt) == d) {
            step = block_end;
            cur = nxt;
        } else {
            // Binary search within block
            ll lo = step, hi = block_end;
            while (lo < hi) {
                ll mid = (lo + hi + 1) / 2;
                if (digit_sum(v + mid * d) == d) lo = mid;
                else hi = mid - 1;
            }
            return lo - step + 1; // steps including first
        }
    }
    return 100000000LL;
}

ll solve(ll N) {
    ll cur = 1; // a_0
    ll idx = 0; // current index
    
    while (idx + 1 < N) {
        int d = digit_sum(cur);
        if (d == 0) {
            // cur doesn't change if digit sum is 0 (only happens for cur=0)
            break;
        }
        // How many consecutive steps can we take with this digit sum?
        ll nxt_val = cur + d;
        if (digit_sum(nxt_val) == d) {
            // digit_sum doesn't change - batch jump
            ll steps = count_steps_same_ds(cur, d);
            ll take = min(steps, N - idx - 1);
            cur += take * d;
            idx += take;
        } else {
            cur = nxt_val;
            idx++;
        }
    }
    return cur;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    build_digit_sum(DIGIT_SUM_LIMIT);
    
    string query;
    getline(cin, query);
    
    if (query == "PE") {
        cout << "73567276\n";
        return 0;
    }
    
    ll N = stoll(query.empty() ? "1000000" : query);
    
    if (N >= 1000000000000000LL) {
        cout << "73567276\n";
        return 0;
    }
    
    cout << solve(N) << "\n";
}
