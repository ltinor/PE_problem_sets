#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 601: Divisibility streaks
// 整除连续串 / 连续整除
//
// streak(n) = smallest k such that n+k not divisible by k+1.
// P(s, N) = count of n in (1, N) with streak(n) = s.
//
// Given: P(3,14)=1, P(6,10^6)=14286.
// Find sum_{i=1}^{31} P(i, 4^i).
//
// PE answer: 1617243
//
// Analysis:
// streak(n) ≥ s iff n ≡ 1 (mod LCM(2,3,...,s)).
// Proof: For k=0,...,s-1: n+k divisible by k+1
//   ⇔ n ≡ -k ≡ 1 (mod k+1)
//   ⇔ n ≡ 1 (mod LCM(2,3,...,s))
//
// So streak(n) = s ⇔ n ≡ 1 (mod L_s) and n ≢ 1 (mod L_{s+1})
// where L_s = lcm(2,3,...,s), L_1 = 1.
//
// P(s, N) = ⌊(N-2)/L_s⌋ - ⌊(N-2)/L_{s+1}⌋
// (n = 1+t*L_s, 1 < n < N ⇒ 2 ≤ n ≤ N-1 ⇒ t ∈ [1, ⌊(N-2)/L_s⌋])

const ll PE_ANSWER = 1617243;

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }

// Count n in (1, N) with streak(n) = s
ll P_count(ll s, ll N) {
    // Compute L_s = lcm(2,...,s)
    ll L_s = 1;
    for (ll i = 2; i <= s; i++) {
        L_s = lcm(L_s, i);
    }
    // Compute L_{s+1} = lcm(2,...,s+1)
    ll L_s1 = lcm(L_s, s + 1);
    
    ll cnt_s = (N - 2) / L_s;
    ll cnt_s1 = (N - 2) / L_s1;
    return cnt_s - cnt_s1;
}

void verify_small() {
    cout << "Verifying known values:\n";
    cout << "P(3, 14) = " << P_count(3, 14) << " (expected 1)\n";
    cout << "P(6, 10^6) = " << P_count(6, 1000000) << " (expected 14286)\n";
    
    // Verify some streak values manually
    cout << "\nStreak values for small n:\n";
    for (ll n = 2; n <= 30; n++) {
        ll s = 1;
        while ((n + s) % (s + 1) == 0) s++;
        cout << "streak(" << n << ") = " << s;
        // Verify formula
        ll L_s = 1;
        for (ll i = 2; i <= s; i++) L_s = lcm(L_s, i);
        ll L_s1 = lcm(L_s, s + 1);
        bool in_set = (n % L_s == 1 % L_s);
        bool in_next = (n % L_s1 == 1 % L_s1);
        cout << (in_set && !in_next ? " ✓" : " ✗") << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    string query;
    getline(cin, query);
    
    if (query == "PE") {
        ll total = 0;
        for (ll i = 1; i <= 31; i++) {
            ll Ni = 1;
            for (int j = 0; j < i; j++) Ni *= 4;
            total += P_count(i, Ni);
        }
        cout << total << "\n";
        return 0;
    }
    
    if (query == "verify") {
        verify_small();
        return 0;
    }
    
    if (query == "compute") {
        ll total = 0;
        for (ll i = 1; i <= 31; i++) {
            ll Ni = 1;
            for (int j = 0; j < i; j++) Ni *= 4;
            ll p = P_count(i, Ni);
            cout << "i=" << i << ": P(" << i << ", 4^" << i << ") = " << p << "\n";
            total += p;
        }
        cout << "Total sum: " << total << "\n";
        return 0;
    }
    
    cout << "PE 601: Divisibility streaks\n";
    cout << "Sum_{i=1}^{31} P(i, 4^i) = " << PE_ANSWER << "\n";
    cout << "Use 'PE' to compute and output the answer.\n";
    cout << "Use 'verify' for small value checks.\n";
    cout << "Use 'compute' to show all terms.\n";
    
    return 0;
}
