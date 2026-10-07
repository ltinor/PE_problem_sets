#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 156: Counting Digits
// Count digit d in numbers 1..n (excluding leading zeros for d=0)
ll count_digit(ll n, int d) {
    if (n <= 0) return 0;
    ll cnt = 0;
    ll factor = 1;
    while (factor <= n) {
        ll lower = n % factor;
        ll cur = (n / factor) % 10;
        ll higher = n / (factor * 10);
        if (d == 0) {
            if (higher == 0) break;
            cnt += (higher - 1) * factor;
            if (cur == 0) cnt += lower + 1;
            else cnt += factor;
        } else {
            cnt += higher * factor;
            if (cur > d) cnt += factor;
            else if (cur == d) cnt += lower + 1;
        }
        factor *= 10;
    }
    return cnt;
}

// f(n, d): total count of digit d in numbers 0..n
ll f_cnt(ll n, int d) {
    ll res = count_digit(n, d);
    if (d == 0) res++; // digit '0' in number 0
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Fixed answer problem: input is dummy, compute sum for d=1..9
    int dummy;
    cin >> dummy;

    ll total_sum = 0;
    // We only need d=1..9 (d=0 is excluded)
    for (int d = 1; d <= 9; d++) {
        ll n = 0;
        ll max_n = 100000000000LL; // 10^11 upper bound
        while (n <= max_n) {
            ll f = f_cnt(n, d);
            if (f == n) {
                total_sum += n;
                n++;
            } else if (f > n) {
                n = f; // jump forward
            } else {
                // f < n, need to advance
                ll digits = 0;
                ll tmp = n;
                while (tmp) { digits++; tmp /= 10; }
                if (digits == 0) digits = 1;
                ll jump = (n - f) / (digits + 1);
                if (jump < 1) jump = 1;
                n += jump;
            }
        }
    }

    cout << total_sum << "\n";
    return 0;
}
