// PE 375 - Minimum of Subsequences
// S_0 = 290797, S_{n+1} = S_n² mod 50515093
// A(i,j) = min(S_i, ..., S_j) for i ≤ j
// M(N) = Σ_{1≤i≤j≤N} A(i,j)
// PE: M(2·10⁹) = 7435327983715286168
//
// Approach: Use monotonic stack to compute contribution of each element
// as the minimum of subarrays. For each position i, find the
// nearest smaller element to the left and right.
// Then A(i,j) = S_k where k is the position of the minimum in [i,j].
// Contribution of position k: S_k * (k - left[k]) * (right[k] - k)
// where left[k] = last position < k with S_pos < S_k (or 0 if none)
// right[k] = first position > k with S_pos < S_k (or N+1 if none)
//
// Sum over all k: S_k * (k - L[k]) * (R[k] - k)
// This computes Σ A(i,j) efficiently in O(N).

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    if (N <= 0) { cout << "0\n"; return 0; }

    // Generate sequence
    const ll MOD = 50515093;
    vector<ll> S(N + 1); // 1-indexed
    S[0] = 290797;
    for (ll i = 1; i <= N; i++) {
        S[i] = S[i-1] * S[i-1] % MOD;
    }

    // Monotonic stack for nearest smaller to the left
    vector<ll> L(N + 1), R(N + 1);
    stack<ll> st;

    // Left: find nearest index < i with S[idx] < S[i]
    for (ll i = 1; i <= N; i++) {
        while (!st.empty() && S[st.top()] >= S[i]) st.pop();
        L[i] = st.empty() ? 0 : st.top();
        st.push(i);
    }

    while (!st.empty()) st.pop();

    // Right: find nearest index > i with S[idx] < S[i]
    for (ll i = N; i >= 1; i--) {
        while (!st.empty() && S[st.top()] >= S[i]) st.pop();
        R[i] = st.empty() ? N + 1 : st.top();
        st.push(i);
    }

    // Sum contributions
    ll ans = 0;
    for (ll i = 1; i <= N; i++) {
        ll left_count = i - L[i];
        ll right_count = R[i] - i;
        ans += S[i] * left_count * right_count;
    }

    cout << ans << "\n";
    return 0;
}
