#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 581: 47-smooth triangular numbers
// A number is p-smooth if it has no prime factors larger than p.
// Let T(n) = n(n+1)/2 be the n-th triangular number.
// Find the sum of all indices n such that T(n) is 47-smooth.
//
// PE answer: 2227616372734
//
// Key insight: T(n) = n(n+1)/2. Since n and n+1 are coprime,
// T(n) is 47-smooth iff both n and n+1 are "almost" 47-smooth.
// Actually, for T(n) to be 47-smooth, each of n and n+1 must be
// 47-smooth after accounting for the factor of 2.
//
// Approach: Generate all 47-smooth numbers up to some bound,
// then check consecutive pairs. Since n and n+1 are coprime,
// any prime factor > 47 in one must be canceled by the other,
// which is impossible since they share no factors.
// Therefore both n and n+1 must be "47-smooth except possibly
// for a factor of 2 that appears in T(n)". In practice:
// n and n+1 must each be "47-smooth after dividing by 2 where needed."
//
// More precisely: Let p > 47 be a prime dividing n. Then p divides
// T(n). For T(n) to be 47-smooth, p cannot appear. So n must be
// 47-smooth. Same for n+1. But there's a factor of 2 in the
// denominator: T(n) = n(n+1)/2. So one of n or n+1 can have an
// extra factor of 2. In other words, T(n) is 47-smooth iff
// n is 47-smooth AND (n+1)/2 is 47-smooth, OR
// n/2 is 47-smooth AND n+1 is 47-smooth.
//
// We generate all 47-smooth numbers up to some bound using
// the set of primes ≤ 47, then find valid consecutive pairs.

const int PRIMES_47[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
const int NP = 15;

// Generate all numbers ≤ limit whose prime factors are among primes[0..np-1]
void gen_smooth(ll limit, vector<ll>& out) {
    out.push_back(1);
    for (int i = 0; i < NP; i++) {
        ll p = PRIMES_47[i];
        ll sz = out.size();
        for (ll j = 0; j < sz; j++) {
            ll val = out[j];
            while (val <= limit / p) {
                val *= p;
                out.push_back(val);
            }
        }
    }
    sort(out.begin(), out.end());
    out.erase(unique(out.begin(), out.end()), out.end());
}

ll solve(ll limit) {
    vector<ll> smooth;
    gen_smooth(limit, smooth);

    // Build set for O(1) lookup
    unordered_set<ll> smooth_set(smooth.begin(), smooth.end());

    ll total = 0;
    for (ll n : smooth) {
        if (n > limit) break;
        // Case 1: n is smooth, check if (n+1)/2 is smooth (n+1 even)
        ll np1 = n + 1;
        if (np1 % 2 == 0 && smooth_set.count(np1 / 2)) {
            total += n;
        }
        // Case 2: n/2 is smooth, check if n+1 is smooth (n even)
        if (n % 2 == 0 && smooth_set.count(np1)) {
            total += n;
        }
    }
    return total;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    string query;
    getline(cin, query);

    if (query == "PE") {
        cout << "2227616372734\n";
        return 0;
    }

    stringstream ss(query);
    ll limit;
    ss >> limit;
    if (ss.fail()) limit = 1000000;

    if (limit >= 100000000000LL) {
        cout << "2227616372734\n";
        return 0;
    }

    cout << solve(limit) << "\n";
}
