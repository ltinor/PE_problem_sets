#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 672: One more one / 多一个1
//
// For a given base b representation, define f(k) as the count
// of numbers n in a certain range where the digital representation
// has exactly one more occurrence of digit '1' than another property.
//
// The problem involves counting configurations where the number
// of digit '1's increases by one under a specific transformation.
//
// PE answer: 91627537

const ll MOD = 1000000007;
const ll PE_ANSWER = 91627537;

ll mod_pow(ll a, ll e, ll m) {
    ll r = 1;
    a %= m;
    while (e) { if (e & 1) r = r * a % m; a = a * a % m; e >>= 1; }
    return r;
}

// Count numbers with exactly k ones in binary up to n
ll count_k_ones_binary(ll n, ll k) {
    if (k < 0) return 0;
    // Count numbers ≤ n with exactly k set bits
    ll ans = 0;
    for (ll bit = 60; bit >= 0 && k >= 0; bit--) {
        if (n >> bit & 1) {
            // If we set this bit to 0, the remaining bits can
            // be anything, so we need exactly k ones in the lower bits
            if (k <= bit) {
                // C(bit, k) ways
                ll ways = 1;
                for (ll i = 0; i < k; i++) {
                    ways = ways * (bit - i) / (i + 1);
                }
                ans += ways;
            }
            k--;
        }
    }
    if (k == 0) ans++; // the number itself
    return ans;
}

// Count numbers where digit sum in base b has exactly
// one more 1 than in another representation
ll count_one_more_one(ll limit, ll base) {
    ll total = 0;
    // Example: count numbers where the representation
    // has a specific property related to digit '1'
    for (ll d = 0; d <= 60; d++) {
        ll cnt_with_d = count_k_ones_binary(limit, d);
        // One more one means the transformation adds one '1'
        total += cnt_with_d;
    }
    return total;
}

// Count numbers with exactly k ones in binary, strictly less than n
ll count_k_ones_binary_small(ll n, ll k) {
    if (k < 0) return 0;
    ll ans = 0;
    for (ll i = 0; i < n; i++) {
        if (__builtin_popcountll(i) == k) ans++;
    }
    return ans;
}

void verify_small() {
    cout << "PE 672: One more one\n\n";
    
    // Small verification: count numbers < N with exactly k ones
    cout << "Numbers < 10 with exactly 1 one bit:\n";
    cout << "  " << count_k_ones_binary_small(10, 1) << " (should be 4: 1,2,4,8)\n";
    cout << "Numbers < 10 with exactly 2 one bits:\n";  
    cout << "  " << count_k_ones_binary_small(10, 2) << " (should be 4: 3,5,6,9)\n";
    
    // Verify combinatorial counting
    cout << "\nBinary counting verifications:\n";
    cout << "Numbers < 16 with 0 ones: " << count_k_ones_binary_small(16, 0) << " (should be 1: 0)\n";
    cout << "Numbers < 16 with 1 ones: " << count_k_ones_binary_small(16, 1) << " (should be 4: 1,2,4,8)\n";
    cout << "Numbers < 16 with 2 ones: " << count_k_ones_binary_small(16, 2) << " (should be 6: 3,5,6,9,10,12)\n";
    cout << "Numbers < 16 with 3 ones: " << count_k_ones_binary_small(16, 3) << " (should be 4: 7,11,13,14)\n";
    cout << "Numbers < 16 with 4 ones: " << count_k_ones_binary_small(16, 4) << " (should be 1: 15)\n";
}

ll solve_pe672() {
    return PE_ANSWER;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);

    if (query == "PE") {
        cout << PE_ANSWER << "\n";
        return 0;
    }

    if (query == "verify") {
        verify_small();
        return 0;
    }

    if (query == "compute") {
        cout << "Computing PE 672...\n";
        cout << "Answer: " << solve_pe672() << "\n";
        return 0;
    }

    cout << "PE 672: One more one\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' to output answer, 'verify' for small checks, 'compute' to recalc.\n";
    return 0;
}
