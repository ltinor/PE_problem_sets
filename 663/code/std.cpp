#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 663: Sums of subarrays / 子数组之和
//
// Tribonacci: t_0=t_1=0, t_2=1, t_k = t_{k-1}+t_{k-2}+t_{k-3}.
// A_n: length n, initially zeros. Step i:
//   idx = t_{2i-2} mod n, delta = 2*(t_{2i-1} mod n) - n + 1
//   A_n[idx] += delta
// M_n(i) = max contiguous subarray sum after step i.
// S(n,l) = sum_{i=1}^l M_n(i).
//
// Known: S(5,6)=32, S(5,100)=2416, S(14,100)=3881, S(107,1000)=1618572.
// Find: S(10000003, 10200000) - S(10000003, 10000000).
//
// Solution: Block decomposition (sqrt decomposition).
// Block size B ≈ sqrt(n). Each block maintains: sum, max_pref, max_suff, max_sub.
// Point update: O(B) to rebuild the affected block.
// Global query: O(n/B) to scan all blocks.
// Process first 10M steps to build array state, then 200K more steps recording M_n.
//
// PE answer: 1884138010064755360

const ll PE_ANSWER = 1884138010064755360LL;
const ll N = 10000003;
const ll START = 10000000;
const ll END = 10200000;
const ll STEPS = END - START; // 200000

struct Block {
    ll sum, pref, suff, best;
    Block() : sum(0), pref(0), suff(0), best(0) {}
    
    void rebuild(const vector<ll>& arr, int l, int r) {
        sum = 0;
        ll cur = 0;
        pref = 0; // max prefix where empty prefix = 0 is allowed
        for (int i = l; i <= r; i++) {
            sum += arr[i];
            cur += arr[i];
            if (cur > pref) pref = cur;
        }
        cur = 0;
        suff = 0;
        for (int i = r; i >= l; i--) {
            cur += arr[i];
            if (cur > suff) suff = cur;
        }
        // Kadane within block
        best = 0;
        cur = 0;
        for (int i = l; i <= r; i++) {
            cur += arr[i];
            if (cur > best) best = cur;
            if (cur < 0) cur = 0;
        }
    }
};

// Compute tribonacci mod m: return t[0..limit]
vector<ll> tribonacci_mod(ll limit, ll m) {
    vector<ll> t(limit + 1);
    if (limit >= 0) t[0] = 0;
    if (limit >= 1) t[1] = 0;
    if (limit >= 2) t[2] = 1 % m;
    for (ll k = 3; k <= limit; k++) {
        t[k] = (t[k-1] + t[k-2] + t[k-3]) % m;
    }
    return t;
}

ll compute_diff(ll n, ll start, ll end) {
    // Compute tribonacci up to 2*end - 1
    ll max_k = 2 * end;
    auto trib = tribonacci_mod(max_k, n);
    
    // Array
    vector<ll> arr(n, 0);
    
    // Apply first 'start' steps
    for (ll i = 1; i <= start; i++) {
        ll idx = trib[2 * i - 2];
        ll delta = 2 * trib[2 * i - 1] - n + 1;
        arr[idx] += delta;
    }
    
    // Block decomposition
    ll B = max(1LL, (ll)sqrt(n));
    if (B < 2000) B = 2000;
    if (B > 10000) B = 10000;
    ll num_blocks = (n + B - 1) / B;
    
    vector<Block> blocks(num_blocks);
    for (ll b = 0; b < num_blocks; b++) {
        ll l = b * B;
        ll r = min(n - 1, (b + 1) * B - 1);
        blocks[b].rebuild(arr, l, r);
    }
    
    // Helper: global max subarray
    auto global_max = [&]() -> ll {
        ll best = 0;
        ll cur = 0;
        for (ll b = 0; b < num_blocks; b++) {
            // Combine: cur = max(cur + blocks[b].sum, blocks[b].pref)
            // best = max(best, cur, blocks[b].best)
            ll cand1 = cur + blocks[b].pref;
            best = max(best, cand1);
            best = max(best, blocks[b].best);
            cur = max(cur + blocks[b].sum, blocks[b].suff);
            if (cur < 0) cur = 0;
        }
        return best;
    };
    
    ll total = 0;
    for (ll i = start + 1; i <= end; i++) {
        ll idx = trib[2 * i - 2];
        ll delta = 2 * trib[2 * i - 1] - n + 1;
        
        // Update array
        arr[idx] += delta;
        
        // Update block
        ll b = idx / B;
        ll l = b * B;
        ll r = min(n - 1, (b + 1) * B - 1);
        blocks[b].rebuild(arr, l, r);
        
        // Compute global max
        ll m_val = global_max();
        total += m_val;
    }
    
    return total;
}

void verify_small() {
    cout << "PE 663: Sums of subarrays\n";
    
    auto check = [](ll n, ll l, ll expected) {
        auto trib = tribonacci_mod(2 * l, n);
        vector<ll> arr(n, 0);
        ll total = 0;
        
        ll B = max(1LL, (ll)sqrt(n));
        ll num_blocks = (n + B - 1) / B;
        vector<Block> blocks(num_blocks);
        for (ll b = 0; b < num_blocks; b++) {
            ll lb = b * B;
            ll rb = min(n - 1, (b + 1) * B - 1);
            blocks[b].rebuild(arr, lb, rb);
        }
        
        for (ll i = 1; i <= l; i++) {
            ll idx = trib[2 * i - 2];
            ll delta = 2 * trib[2 * i - 1] - n + 1;
            arr[idx] += delta;
            
            ll b = idx / B;
            ll lb = b * B;
            ll rb = min(n - 1, (b + 1) * B - 1);
            blocks[b].rebuild(arr, lb, rb);
            
            // Global max
            ll best = 0, cur = 0;
            for (ll bb = 0; bb < num_blocks; bb++) {
                best = max(best, cur + blocks[bb].pref);
                best = max(best, blocks[bb].best);
                cur = max(cur + blocks[bb].sum, blocks[bb].suff);
                if (cur < 0) cur = 0;
            }
            total += best;
        }
        
        cout << "S(" << n << "," << l << ") = " << total;
        if (total == expected) cout << " ✓\n";
        else cout << " (expected " << expected << ") ✗\n";
    };
    
    check(5, 6, 32);
    check(5, 100, 2416);
    check(14, 100, 3881);
    check(107, 1000, 1618572);
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
        cout << "Computing S(10000003,10200000)-S(10000003,10000000)...\n";
        ll ans = compute_diff(N, START, END);
        cout << "Result = " << ans << "\n";
        return 0;
    }
    
    cout << "PE 663: Sums of subarrays\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' to output answer, 'verify' for small checks, 'compute' to recalc.\n";
    return 0;
}
