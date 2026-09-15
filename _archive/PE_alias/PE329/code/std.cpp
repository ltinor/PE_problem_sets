#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE329: Prime Frog / Probabilistic Toad
// Frog jumps on 1..N squares, left/right with equal prob (bounces at edges).
// On prime: croaks 'P' with 2/3, 'N' with 1/3.
// On non-prime: croaks 'P' with 1/3, 'N' with 2/3.
// Starting position uniformly random.
// Given target sequence S, find probability of hearing S
// (15 croaks after starting, croak before each jump).
// Output as reduced fraction p/q.

// DP: dp[pos][t] = probability of being at pos after t croaks
// matching the first t characters of target.
// We use big integers for exact rational arithmetic.

typedef __int128 i128;

i128 gcd(i128 a, i128 b) {
    while (b) { i128 t = b; b = a % b; a = t; }
    return a;
}

vector<bool> sieve(ll n) {
    vector<bool> p(n+1, true);
    p[0] = p[1] = false;
    for (ll i = 2; i*i <= n; i++)
        if (p[i])
            for (ll j = i*i; j <= n; j += i)
                p[j] = false;
    return p;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll N;
    string S;
    cin >> N >> S;
    ll T = (ll)S.size();
    
    auto isp = sieve(N);
    
    // dp_num[pos][t] = numerator of probability
    // Common denominator for all states at step t
    // Initial: probability 1/N for each pos, denominator N
    // Transitions multiply by 1/2 (jump) and 1/3 or 2/3 (croak)
    // Use common denominator approach
    
    // We'll store probabilities as rational numbers:
    // prob = num / den where den is a power of 2*3 times N
    
    // At step t, denominator = N * 3^t * 2^t
    // dp[pos][t] stores the numerator for this denominator
    
    vector<vector<i128>> dp(N+1, vector<i128>(T+1, 0));
    
    // Initialize: dp[pos][0] = 1 for all pos (numerator, denom = N)
    for (ll pos = 1; pos <= N; pos++) {
        dp[pos][0] = 1;
    }
    
    for (ll t = 0; t < T; t++) {
        char target = S[t];
        for (ll pos = 1; pos <= N; pos++) {
            if (dp[pos][t] == 0) continue;
            
            // Croak probability at current position
            i128 croak_factor;
            if (target == 'P') {
                croak_factor = isp[pos] ? 2 : 1;
            } else {
                croak_factor = isp[pos] ? 1 : 2;
            }
            // The croak_factor is numerator when denominator is 3
            
            // Determine jump targets
            vector<ll> next_positions;
            if (pos == 1) next_positions = {2};
            else if (pos == N) next_positions = {(ll)(N-1)};
            else next_positions = {(ll)(pos-1), (ll)(pos+1)};
            
            for (ll nxt : next_positions) {
                // dp[pos][t] / (N * 3^t * 2^t) * croak_factor/3 * 1/(#options)
                // Jump prob: 1 for edges, 1/2 for interior
                i128 jump_den = (next_positions.size() == 1) ? 1 : 2;
                
                // New numerator: dp[pos][t] * croak_factor * 1
                // New denominator factor: 3 * jump_den
                // dp[nxt][t+1] += dp[pos][t] * croak_factor * (common_den_factor)
                
                // At step t: common denom = N * 3^t * 2^t
                // At step t+1: common denom = N * 3^{t+1} * 2^{t+1}
                // Factor to convert: multiply numerator by 3 * jump_den
                // But we want dp[nxt][t+1] / (N * 3^{t+1} * 2^{t+1}) 
                // = dp[pos][t] / (N * 3^t * 2^t) * croak_factor/3 * 1/jump_den
                // So dp[nxt][t+1] = dp[pos][t] * croak_factor * 2 / jump_den
                // (multiply by 2 because denominator gains factor 2 and 3,
                //  but we only have 1/3 * 1/jump_den, so we need factor 2/jump_den * ...)
                
                // Let me redo: common_den_t = N * 3^t * 2^t
                // prob transition: prob_t * (croak_factor/3) * (1/jump_den)
                // prob_{t+1} = prob_t * croak_factor / (3 * jump_den)
                // dp[pos][t] / common_den_t * croak_factor / (3 * jump_den)
                // = dp[pos][t] * croak_factor * 2 / (common_den_{t+1} * jump_den / ...)
                
                // common_den_{t+1} = N * 3^{t+1} * 2^{t+1} = common_den_t * 3 * 2
                // dp[nxt][t+1] / common_den_{t+1} = dp[pos][t] / common_den_t * croak_factor/3 * 1/jump_den
                // dp[nxt][t+1] = dp[pos][t] * croak_factor * 2 / jump_den
                
                // Check: if jump_den=2: contribution = dp[pos][t] * croak_factor * 2 / 2
                //        = dp[pos][t] * croak_factor. Correct!
                // if jump_den=1: contribution = dp[pos][t] * croak_factor * 2
                
                i128 contrib = dp[pos][t] * croak_factor * 2 / jump_den;
                dp[nxt][t+1] += contrib;
            }
        }
    }
    
    // Total numerator = sum over all pos of dp[pos][T]
    i128 num = 0;
    for (ll pos = 1; pos <= N; pos++) {
        num += dp[pos][T];
    }
    
    // Denominator = N * 3^T * 2^T
    i128 den = N;
    for (ll t = 0; t < T; t++) den *= 6; // 3 * 2 = 6
    
    // Reduce fraction
    i128 g = gcd(num, den);
    num /= g;
    den /= g;
    
    // Output
    auto print_i128 = [](i128 x) {
        if (x == 0) { cout << "0"; return; }
        string s;
        while (x > 0) { s = char('0' + (int)(x % 10)) + s; x /= 10; }
        cout << s;
    };
    
    print_i128(num);
    cout << "/";
    print_i128(den);
    cout << "\n";
    
    return 0;
}
