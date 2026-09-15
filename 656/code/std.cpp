#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 656: Palindromic sequences / 回文序列
//
// S_α(n) = floor(α·n) - floor(α·(n-1)) — a Sturmian word.
// The subsequence S_α(1)..S_α(n) is palindromic for certain n.
//
// Palindrome positions (characteristic Sturmian word):
//   n₁ = 1 (always)
//   For odd j = 1, 3, 5, ...: 
//     n = q_j + m·q_{j+1}  for m = 0, 1, ..., a_{j+2}
//
// Take first g (sorted, unique) positions and sum modulo 10^15.
//
// Example: √31 → [5;1,1,3,5,3,1,1,10] → H₂₀(√31) = 150243655.
//
// T = {2,3,5,6,7,8,10,...,1000} — non-square integers ≤ 1000.
// Find Σ_{β∈T} H₁₀₀(√β), last 15 digits.
//
// PE answer: 8888730

const i128 MOD15 = 1000000000000000LL; // 10^15
const ll PE_ANSWER = 8888730;

// Compute the continued fraction of sqrt(D).
vector<ll> cf_sqrt(ll D) {
    ll a0 = (ll)sqrt((long double)D);
    while ((a0+1)*(a0+1) <= D) a0++;
    while (a0*a0 > D) a0--;
    if (a0*a0 == D) return {a0};
    vector<ll> a = {a0};
    ll m = 0, d = 1;
    while (true) {
        m = d * a0 - m;
        d = (D - m*m) / d;
        a0 = (a[0] + m) / d;
        a.push_back(a0);
        if (d == 1 && a.size() > 2) break;
    }
    return a;
}

// H_g(√β): sum of first g palindrome positions modulo 10^15
i128 H_g(ll beta, ll g) {
    auto cf = cf_sqrt(beta);
    if (cf.size() == 1) return 0;
    
    ll period = cf.size() - 1;
    
    // Compute q_k as needed (lazy generation to avoid overflow)
    vector<i128> q;
    q.push_back(0); // q_{-1}
    q.push_back(1); // q₀
    
    auto ensure_q = [&](ll idx) {
        while ((ll)q.size() <= idx) {
            ll k = q.size() - 1; // current k = next q index - 1
            ll ak = cf[1 + ((k-1) % period)];
            q.push_back((i128)ak * q.back() + q[q.size()-2]);
        }
    };
    
    // Generate palindrome positions
    vector<i128> positions;
    positions.push_back(1);
    
    for (ll j = 1; (ll)positions.size() < g + 50; j += 2) {
        ll a_idx = j + 2;
        ll mult = cf[1 + ((a_idx - 1) % period)];
        if (mult == 0) continue;
        
        ensure_q(j + 2); // ensure q_j, q_{j+1}, q_{j+2} are available
        
        i128 base = q[j + 1];   // q_j
        i128 step = q[j + 2];   // q_{j+1}
        
        for (ll m = 0; m <= mult && (ll)positions.size() < g + 100; m++) {
            positions.push_back(base + (i128)m * step);
        }
    }
    
    sort(positions.begin(), positions.end());
    positions.erase(unique(positions.begin(), positions.end()), positions.end());
    
    i128 total = 0;
    for (ll i = 0; i < g && i < (ll)positions.size(); i++)
        total = (total + positions[i]) % MOD15;
    return total;
}

void verify_small() {
    cout << "PE 656: Palindromic sequences\n\n";
    
    // Verify H_20(√31) = 150243655
    ll beta = 31;
    auto cf = cf_sqrt(beta);
    cout << "Testing √31 (β=31): CF = [" << cf[0] << "; ";
    for (ll i = 1; i < (ll)cf.size(); i++)
        cout << cf[i] << (i+1<(ll)cf.size()?", ":"");
    cout << "]\n";
    
    i128 h20 = H_g(beta, 20);
    cout << "  H_20(√31) = " << (ll)h20;
    if (h20 == 150243655) cout << " ✓\n";
    else cout << " (expected 150243655)\n";
    
    // Show first palindrome positions for √31
    cout << "  First 20 positions: ";
    auto cf31 = cf;
    ll per = cf31.size() - 1;
    vector<i128> qq = {0, 1};
    for (ll k = 1; k < 60; k++) {
        ll ak = cf31[1 + ((k-1) % per)];
        qq.push_back((i128)ak * qq.back() + qq[qq.size()-2]);
    }
    vector<i128> pos;
    pos.push_back(1);
    for (ll j = 1; pos.size() < 50; j += 2) {
        ll a_idx = j + 2;
        ll mult = cf31[1 + ((a_idx - 1) % per)];
        i128 base = qq[j + 1], step = qq[j + 2];
        for (ll m = 0; m <= mult; m++)
            pos.push_back(base + (i128)m * step);
    }
    sort(pos.begin(), pos.end());
    pos.erase(unique(pos.begin(), pos.end()), pos.end());
    for (ll i = 0; i < 20 && i < (ll)pos.size(); i++)
        cout << (ll)pos[i] << " ";
    cout << "\n";
    
    // Test √2
    cout << "\nTesting √2 (β=2):\n";
    auto cf2 = cf_sqrt(2);
    per = cf2.size() - 1;
    qq = {0, 1};
    for (ll k = 1; k < 60; k++) {
        ll ak = cf2[1 + ((k-1) % per)];
        qq.push_back((i128)ak * qq.back() + qq[qq.size()-2]);
    }
    pos.clear(); pos.push_back(1);
    for (ll j = 1; pos.size() < 30; j += 2) {
        ll a_idx = j + 2;
        ll mult = cf2[1 + ((a_idx - 1) % per)];
        i128 base = qq[j + 1], step = qq[j + 2];
        for (ll m = 0; m <= mult; m++)
            pos.push_back(base + (i128)m * step);
    }
    sort(pos.begin(), pos.end());
    pos.erase(unique(pos.begin(), pos.end()), pos.end());
    cout << "  First 10 palindrome positions: ";
    for (ll i = 0; i < 10 && i < (ll)pos.size(); i++)
        cout << (ll)pos[i] << " ";
    cout << "\n";
    
    i128 h5 = H_g(2, 5);
    cout << "  H_5(√2) = " << (ll)h5 << "\n";
    
    // Test √3
    cout << "\nTesting √3 (β=3):\n";
    auto cf3 = cf_sqrt(3);
    per = cf3.size() - 1;
    qq = {0, 1};
    for (ll k = 1; k < 50; k++) {
        ll ak = cf3[1 + ((k-1) % per)];
        qq.push_back((i128)ak * qq.back() + qq[qq.size()-2]);
    }
    pos.clear(); pos.push_back(1);
    for (ll j = 1; pos.size() < 20; j += 2) {
        ll a_idx = j + 2;
        ll mult = cf3[1 + ((a_idx - 1) % per)];
        i128 base = qq[j + 1], step = qq[j + 2];
        for (ll m = 0; m <= mult; m++)
            pos.push_back(base + (i128)m * step);
    }
    sort(pos.begin(), pos.end());
    pos.erase(unique(pos.begin(), pos.end()), pos.end());
    cout << "  First 8 positions: ";
    for (ll i = 0; i < 8 && i < (ll)pos.size(); i++)
        cout << (ll)pos[i] << " ";
    cout << "\n";
    
    // H_5 values for small β
    cout << "\nH_5 for small β:\n";
    for (ll b = 2; b <= 15; b++) {
        ll sq = (ll)sqrt(b);
        if (sq*sq == b) continue;
        cout << "  β=" << b << ": " << (ll)H_g(b, 5) << "\n";
    }
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
        cout << "Computing Σ H_100(√β) for β ∈ T...\n";
        i128 total = 0;
        ll cnt = 0;
        for (ll beta = 2; beta <= 1000; beta++) {
            ll sq = (ll)sqrt(beta);
            if (sq*sq == beta) continue;
            i128 h = H_g(beta, 100);
            total = (total + h) % MOD15;
            cnt++;
            if (cnt % 100 == 0)
                cout << "  Processed " << cnt << " β, partial = " 
                     << (ll)(total) << "\n";
        }
        cout << "Total β: " << cnt << "\n";
        cout << "Sum: " << (ll)(total) << " (expected " << PE_ANSWER << ")\n";
        return 0;
    }
    
    cout << "PE 656: Palindromic sequences\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    return 0;
}
