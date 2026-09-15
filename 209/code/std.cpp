#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 209: Circular Logic
// Count truth tables τ: {0,1}^k → {0,1} satisfying:
// τ(a) AND τ(T(a)) = 0 for all a, where
// T(a_0,...,a_{k-1}) = (a_1,...,a_{k-1}, a_0 XOR (a_1 AND a_2))
// (for k >= 3; for k < 3, T(a) = (a_1,...,a_{k-1}, a_0 XOR ...))
// 
// T is a permutation on 2^k states.
// The constraint means the set of states where τ=1 must be an independent set
// in the functional digraph of T.
// For a cycle of length L: count = F_{L-1} + F_{L+1}
// For L=1: count = 1 (must be 0)
// Answer = Π_{cycles} (F_{L_i-1} + F_{L_i+1})

void print_i128(__int128 x) {
    if (x == 0) { cout << "0"; return; }
    string s;
    while (x) { s += char('0' + (int)(x % 10)); x /= 10; }
    reverse(s.begin(), s.end());
    cout << s;
}

// Compute T(s) for k-bit state s
ll T(ll s, int k) {
    // s = a_0 + a_1*2 + a_2*4 + ... + a_{k-1}*2^{k-1}
    // Extract bits
    ll a0 = s & 1;
    ll a1 = (s >> 1) & 1;
    ll a2 = (s >> 2) & 1;
    // New state: shift right, then set MSB = a0 XOR (a1 AND a2)
    ll shifted = s >> 1;
    ll new_msb = a0 ^ (a1 & a2);
    // Clear old MSB and set new one
    ll mask = (1LL << (k - 1)) - 1;
    ll res = (shifted & mask) | (new_msb << (k - 1));
    return res;
}

// Fibonacci numbers (up to large values)
// F_0 = 0, F_1 = 1
// cycle_count[L] = F_{L-1} + F_{L+1}
// For L=1: F_0 + F_2 = 0 + 1 = 1
// For L=2: F_1 + F_3 = 1 + 2 = 3

// Use __int128 for Fibonacci
__int128 cycle_count(int L) {
    if (L == 1) return 1;
    // Compute F_{L-1} and F_{L+1}
    // F_n: 0,1,1,2,3,5,8,13,21,34,55,...
    __int128 f_prev = 0, f_curr = 1;
    for (int i = 1; i <= L + 1; i++) {
        __int128 f_next = f_prev + f_curr;
        f_prev = f_curr;
        f_curr = f_next;
        if (i == L - 1) {
            // Save F_{L-1}
        }
    }
    // After loop: f_prev = F_{L+1}, but need both F_{L-1} and F_{L+1}
    // Let me recompute properly
    // Actually: after i iterations starting from F_0=0, F_1=1:
    // i=1: f_curr=1 (F_1), f_prev=0 (F_0)
    // i=2: f_curr=1 (F_2), f_prev=1 (F_1)
    // i=3: f_curr=2 (F_3), f_prev=1 (F_2)
    // So after i iterations, f_curr = F_i, f_prev = F_{i-1}
    
    // We need F_{L-1} + F_{L+1}
    // After L-1 iterations: f_curr = F_{L-1}, f_prev = F_{L-2}
    // After L+1 iterations: f_curr = F_{L+1}
    // So compute both
    __int128 fa = 0, fb = 1; // F_0, F_1
    for (int i = 1; i < L - 1; i++) {
        __int128 fc = fa + fb;
        fa = fb;
        fb = fc;
    }
    __int128 FLm1 = (L - 1 >= 1) ? fb : ((L - 1 == 0) ? 0 : 0);
    // Continue to F_{L+1}
    if (L - 1 < 1) {
        fa = 0; fb = 1;
        for (int i = 1; i < L + 1; i++) {
            __int128 fc = fa + fb;
            fa = fb; fb = fc;
        }
    }
    __int128 FLp1 = fb;
    for (int i = max(1, L - 1); i < L + 1; i++) {
        __int128 fc = fa + fb;
        fa = fb; fb = fc;
    }
    // Actually let me just do simple computation
    __int128 f[200];
    f[0] = 0; f[1] = 1;
    for (int i = 2; i <= L + 1; i++) {
        f[i] = f[i-1] + f[i-2];
    }
    return f[L-1] + f[L+1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    cin >> k;

    if (k < 1 || k > 7) {
        cout << "0\n";
        return 0;
    }

    ll total_states = 1LL << k;
    vector<bool> visited(total_states, false);

    __int128 ans = 1;

    for (ll s = 0; s < total_states; s++) {
        if (visited[s]) continue;

        // Follow cycle
        ll cur = s;
        int len = 0;
        while (!visited[cur]) {
            visited[cur] = true;
            len++;
            cur = T(cur, k);
        }

        // Multiply by cycle count
        __int128 cc = cycle_count(len);
        ans = ans * cc;
    }

    print_i128(ans);
    cout << "\n";
    return 0;
}
