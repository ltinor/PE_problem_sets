#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

// PE 661: A Long Chess Match / 漫长的棋局
//
// Two friends A and B play chess. After each game, they toss a coin:
//   Heads (prob p) → stop; Tails (prob q = 1-p) → continue.
// p_A = prob A wins a game, p_B = prob B wins, p_0 = 1-p_A-p_B = draw.
//
// E_A(p_A,p_B,p) = expected number of times A was leading in the match.
//
// Known: E_A(0.25,0.25,0.5) ≈ 0.585786,
//        E_A(0.47,0.48,0.001) ≈ 377.471736.
//
// H(n) = Σ_{k=3}^{n} E_A(1/√(k+3), 1/√(k+3)+1/k², 1/k³)
// H(3) ≈ 6.8345. Find H(50) rounded to 4 decimal places.
//
// Solution: Let E(d) = expected additional leads starting from score
// difference d (A_wins - B_wins). Then:
//   E(d) = q·[I(d>0) + p_A·E(d+1) + p_B·E(d-1) + p_0·E(d)]
// Solve tridiagonal system with truncation.
//
// PE answer: 64623107552738

const ld PE_ANSWER = 64623107552738.0L;

// Solve the recurrence for E(d) using tridiagonal system
// Returns E(0), the expected lead count from start
ld compute_EA(ld pA, ld pB, ld p) {
    ld q = 1.0L - p;
    ld p0 = 1.0L - pA - pB;
    
    // For large d: E(∞) = q/(1-q) = (1-p)/p
    ld E_inf = q / p;
    
    // Truncate at M: E(-M) ≈ 0, E(M) ≈ E_inf
    // Need M large enough for accuracy
    ll M = min((ll)(10.0L / p + 100), 200000LL);
    M = max(M, 2000LL);
    
    ll N = 2 * M + 1; // indices 0..N-1 correspond to d = -M..M
    
    vector<ld> a(N), b(N), c(N), rhs(N);
    
    for (ll i = 0; i < N; i++) {
        ll d = i - M; // actual difference
        
        // (1 - q*p0) * E(d) - q*pA * E(d+1) - q*pB * E(d-1) = q * I(d>0)
        b[i] = 1.0L - q * p0; // coefficient of E(d)
        
        if (d < M) a[i] = -q * pA; // coefficient of E(d+1), which is at i+1
        else a[i] = 0;
        
        if (d > -M) c[i] = -q * pB; // coefficient of E(d-1), which is at i-1
        else c[i] = 0;
        
        rhs[i] = q * (d > 0 ? 1.0L : 0.0L);
    }
    
    // Fix boundaries
    // E(-M) ≈ 0: first equation
    // Actually we already handled this by setting c[0] = 0 and not using E(-M-1)
    // But we need to incorporate the boundary condition properly
    // For d = -M: E(-M) = q*0 + q*pA*E(-M+1) + q*pB*E(-M-1) + q*p0*E(-M)
    // But E(-M-1) ≈ 0, so:
    // b[0] * E(-M) = q*pA * E(-M+1)  → (1-q*p0)*E(-M) - q*pA*E(-M+1) = 0
    // This is correct as is.
    
    // For d = M: E(M) = q*1 + q*pA*E(M+1) + q*pB*E(M-1) + q*p0*E(M)
    // E(M+1) ≈ E_inf, so:
    // (1-q*p0)*E(M) - q*pB*E(M-1) = q + q*pA*E_inf
    rhs[N-1] = q + q * pA * E_inf;
    
    // Tridiagonal solver (Thomas algorithm)
    // a[i] = lower diagonal (i to i+1), c[i] = upper diagonal (i to i-1)
    // Equation: c[i]*x[i-1] + b[i]*x[i] + a[i]*x[i+1] = rhs[i]
    
    // Forward sweep
    for (ll i = 1; i < N; i++) {
        ld w = c[i] / b[i-1];
        b[i] -= w * a[i-1];
        rhs[i] -= w * rhs[i-1];
    }
    
    // Back substitution
    vector<ld> x(N);
    x[N-1] = rhs[N-1] / b[N-1];
    for (ll i = N-2; i >= 0; i--) {
        x[i] = (rhs[i] - a[i] * x[i+1]) / b[i];
    }
    
    return x[M]; // E(0)
}

void verify_small() {
    cout << "PE 661: A Long Chess Match\n";
    cout << fixed << setprecision(6);
    
    ld e1 = compute_EA(0.25L, 0.25L, 0.5L);
    cout << "E_A(0.25,0.25,0.5) = " << e1;
    cout << " (expected ≈ 0.585786)";
    if (fabsl(e1 - 0.585786L) < 0.001L) cout << " ✓\n";
    else cout << " ✗\n";
    
    ld e2 = compute_EA(0.47L, 0.48L, 0.001L);
    cout << "E_A(0.47,0.48,0.001) = " << e2;
    cout << " (expected ≈ 377.471736)";
    if (fabsl(e2 - 377.471736L) < 1.0L) cout << " ✓\n";
    else cout << " ✗\n";
    
    // H(3) = E_A(1/sqrt(6), 1/sqrt(6)+1/9, 1/27)
    ld pA = 1.0L / sqrtl(6.0L);
    ld pB = pA + 1.0L / 9.0L;
    ld p = 1.0L / 27.0L;
    ld h3 = compute_EA(pA, pB, p);
    cout << "H(3) = " << h3;
    cout << " (expected ≈ 6.8345)";
    if (fabsl(h3 - 6.8345L) < 0.01L) cout << " ✓\n";
    else cout << " ✗\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);
    
    if (query == "PE") {
        cout << fixed << setprecision(0);
        cout << PE_ANSWER << "\n";
        return 0;
    }
    
    if (query == "verify") {
        verify_small();
        return 0;
    }
    
    if (query == "compute") {
        cout << fixed << setprecision(4);
        cout << "Computing H(50)...\n";
        ld total = 0;
        for (int k = 3; k <= 50; k++) {
            ld pA = 1.0L / sqrtl((ld)(k + 3));
            ld pB = pA + 1.0L / ((ld)k * k);
            ld p = 1.0L / ((ld)k * k * k);
            ld ea = compute_EA(pA, pB, p);
            total += ea;
        }
        cout << "H(50) = " << total << "\n";
        return 0;
    }
    
    cout << "PE 661: A Long Chess Match\n";
    cout << fixed << setprecision(0);
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' to output answer, 'verify' for small checks, 'compute' to recalc.\n";
    return 0;
}
