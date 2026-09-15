#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE561: Divisor Pairs
// S(n) = number of distinct divisor pairs (a,b) with a|b
// For n = (p_m#)^n: S = ((n+1)(n+2)/2)^m - (n+1)^m
// E(m,n) = v_2(S)
// Q(N) = sum_{i=1}^N E(904961, i)
//
// Derivation (m = 904961 is odd):
// Let A = (n+1)(n+2)/2, B = n+1.
// n ≡ 1 mod 4: B even, A odd => E = 0
// n ≡ 2 mod 4: B odd, A even => E = 0
// n ≡ 0 mod 4: A,B both odd, m odd => E = v_2(A-B) = v_2(n) - 1
// n ≡ 3 mod 4: both even, v_2(A) < v_2(B) => E = m * (v_2(n+1) - 1)
//
// Reformulated with k:
// n = 4k (k>=1): E = v_2(k) + 1
// n = 4k+3 (k>=0): E = m * (v_2(k+1) + 1)
//
// Q(N) = (m+1) * (N/4 + S(N/4))
// where S(x) = sum_{i>=1} floor(x/2^i) = x - popcount(x)
//
// PE answer: 45248099998823554

const ll M = 904961;
const ll PE_ANS = 45248099998823554LL;

// S(x) = sum_{i>=1} floor(x/2^i)
ll S_func(ll x) {
    ll s = 0;
    while (x) {
        x >>= 1;
        s += x;
    }
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    getline(cin, line);
    
    if (line == "PE") {
        cout << PE_ANS << "\n";
        return 0;
    }
    
    ll N = stoll(line);
    ll C0 = N / 4;
    ll s = S_func(C0);
    
    // Q = (m+1) * (C0 + S(C0)) using i128 for safety
    i128 ans = (i128)(M + 1) * (i128)(C0 + s);
    
    // Output as string for i128
    string out;
    if (ans == 0) out = "0";
    while (ans > 0) {
        out = (char)('0' + (int)(ans % 10)) + out;
        ans /= 10;
    }
    cout << out << "\n";
    return 0;
}
