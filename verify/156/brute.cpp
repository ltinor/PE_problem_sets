#include<bits/stdc++.h>
using namespace std;
#define ll long long

// Brute force digit count for verification (small n only)
ll brute_count_digit(ll n, int d) {
    ll cnt = 0;
    for (ll i = 0; i <= n; i++) {
        if (i == 0) {
            if (d == 0) cnt++;
            continue;
        }
        ll tmp = i;
        while (tmp) {
            if (tmp % 10 == d) cnt++;
            tmp /= 10;
        }
    }
    return cnt;
}

// Efficient count digit (same as std for verification)
ll fast_count_digit(ll n, int d) {
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

ll f_fast(ll n, int d) {
    ll res = fast_count_digit(n, d);
    if (d == 0) res++;
    return res;
}

ll f_brute(ll n, int d) {
    return brute_count_digit(n, d);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Input: n d
    ll n;
    int d;
    cin >> n >> d;

    // Verify fast vs brute for small n
    if (n <= 1000000) {
        ll b = f_brute(n, d);
        ll f = f_fast(n, d);
        if (b != f) {
            cerr << "MISMATCH: n=" << n << " d=" << d << " brute=" << b << " fast=" << f << endl;
            return 1;
        }
    }

    // Output result using fast method
    ll f_val = f_fast(n, d);

    // For verification: if this is a solution to f(n,d)=n, output 1 else 0
    if (n == f_val) {
        cout << "1 " << f_val << "\n";
    } else {
        cout << "0 " << f_val << "\n";
    }

    return 0;
}
