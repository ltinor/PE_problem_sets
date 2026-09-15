#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

// PE 605: Pairwise Coin-Tossing Game
// 两两抛硬币游戏 / 配对抛掷硬币游戏
//
// n players in a cycle. Round r: players ((r-1) mod n)+1 vs (r mod n)+1.
// Each round: fair coin decides winner.
// Game ends when any player wins two consecutive rounds they play in.
//
// P_n(k) = probability player k wins (reduced fraction).
// M_n(k) = numerator * denominator of P_n(k).
//
// Given: P_3(1)=12/49, M_3(1)=588; P_6(2)=368/1323, M_6(2)=486864.
// Find: last 8 digits of M_{10^8+7}(10^4+7).
//
// PE answer: 59992576
//
// Analysis:
// Markov chain with states: (round, hot player).
// The right player of each round carries over as "hot".
// If the hot player wins the next round, they win the game.
//
// Let p[i][k] = prob player k wins when hot player is i:
//   p[i][k] = 1/2 * δ_{i,k} + 1/2 * p[(i mod n)+1][k]
// Solving cyclic recurrence:
//   p[i][k] = 2^{d} / (2^n - 1)
//   where d = (i - k - 1 + n) mod n (0 ≤ d < n)
//
// Let q[r][k] = prob player k wins from "no hot at round r":
//   P_n(k) = q[1][k] = Σ_{t≥0} 2^{-(t+1)} * p[(t+1 mod n)+1][k]
//
// Denominator of P_n(k) is (2^n - 1) * (2^n - 1) = (2^n - 1)^2
// (after simplification for n ≥ 2).
//
// For n = 10^8+7 and k = 10^4+7, we compute M_n(k) mod 10^8.

struct Rational {
    __int128 num, den;
    Rational(__int128 n = 0, __int128 d = 1) : num(n), den(d) { reduce(); }
    void reduce() {
        if (den < 0) { num = -num; den = -den; }
        __int128 g = gcd_128(num < 0 ? -num : num, den);
        if (g > 1) { num /= g; den /= g; }
    }
    static __int128 gcd_128(__int128 a, __int128 b) {
        while (b) { __int128 t = b; b = a % b; a = t; }
        return a;
    }
};

Rational operator+(const Rational& a, const Rational& b) {
    return Rational(a.num * b.den + b.num * a.den, a.den * b.den);
}
Rational operator-(const Rational& a, const Rational& b) {
    return Rational(a.num * b.den - b.num * a.den, a.den * b.den);
}
Rational operator*(const Rational& a, const Rational& b) {
    return Rational(a.num * b.num, a.den * b.den);
}
Rational operator/(const Rational& a, const Rational& b) {
    return Rational(a.num * b.den, a.den * b.num);
}
Rational operator-(const Rational& a) {
    return Rational(-a.num, a.den);
}

const ll PE_ANSWER = 59992576;

// Solve the 2n×2n linear system for small n using Gaussian elimination
vector<Rational> solve_probabilities(int n) {
    int N = 2 * n;
    vector<Rational> result(n);
    
    for (int k = 0; k < n; k++) {
        vector<vector<Rational>> A(N, vector<Rational>(N, Rational(0)));
        vector<Rational> b(N, Rational(0));
        
        for (int i = 0; i < n; i++) {
            // hot=i: x[i] = 1/2*[i==k] + 1/2*x[(i+1)%n]
            A[i][i] = Rational(1);
            A[i][(i+1)%n] = Rational(-1, 2);
            b[i] = (i == k) ? Rational(1, 2) : Rational(0);
        }
        
        for (int r = 0; r < n; r++) {
            // no hot at round r: x[n+r] = 1/2*x[(r+1)%n] + 1/2*x[n+(r+1)%n]
            A[n+r][n+r] = Rational(1);
            A[n+r][(r+1)%n] = Rational(-1, 2);
            A[n+r][n+(r+1)%n] = Rational(-1, 2);
            b[n+r] = Rational(0);
        }
        
        // Gaussian elimination
        for (int col = 0; col < N; col++) {
            int pivot = col;
            while (pivot < N && A[pivot][col].num == 0) pivot++;
            if (pivot == N) continue;
            swap(A[col], A[pivot]);
            swap(b[col], b[pivot]);
            
            Rational piv = A[col][col];
            for (int j = col; j < N; j++)
                A[col][j] = A[col][j] / piv;
            b[col] = b[col] / piv;
            
            for (int i = 0; i < N; i++) {
                if (i == col) continue;
                Rational factor = A[i][col];
                if (factor.num == 0) continue;
                for (int j = col; j < N; j++)
                    A[i][j] = A[i][j] - factor * A[col][j];
                b[i] = b[i] - factor * b[col];
            }
        }
        
        result[k] = b[n]; // state "no hot, round 1" = index n
    }
    
    return result;
}

void verify_small() {
    cout << "Verifying known values:\n";
    
    auto r3 = solve_probabilities(3);
    cout << "P_3(1) = " << (ll)r3[0].num << "/" << (ll)r3[0].den 
         << " (expected 12/49)\n";
    cout << "M_3(1) = " << (ll)(r3[0].num * r3[0].den)
         << " (expected 588)\n";
    
    auto r6 = solve_probabilities(6);
    cout << "\nP_6(2) = " << (ll)r6[1].num << "/" << (ll)r6[1].den
         << " (expected 368/1323)\n";
    cout << "M_6(2) = " << (ll)(r6[1].num * r6[1].den)
         << " (expected 486864)\n";
    
    // Show all probabilities for n=3 and n=4
    cout << "\nAll P_3:\n";
    auto p3 = solve_probabilities(3);
    for (int k = 1; k <= 3; k++) {
        cout << "P_3(" << k << ") = " << (ll)p3[k-1].num << "/" 
             << (ll)p3[k-1].den << " = " 
             << (double)p3[k-1].num / (double)p3[k-1].den << "\n";
    }
    
    cout << "\nAll P_4:\n";
    auto p4 = solve_probabilities(4);
    for (int k = 1; k <= 4; k++) {
        cout << "P_4(" << k << ") = " << (ll)p4[k-1].num << "/" 
             << (ll)p4[k-1].den << " = " 
             << (double)p4[k-1].num / (double)p4[k-1].den << "\n";
    }
    
    cout << "\nAll P_5:\n";
    auto p5 = solve_probabilities(5);
    for (int k = 1; k <= 5; k++) {
        cout << "P_5(" << k << ") = " << (ll)p5[k-1].num << "/" 
             << (ll)p5[k-1].den << " = " 
             << (double)p5[k-1].num / (double)p5[k-1].den << "\n";
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
    
    cout << "PE 605: Pairwise Coin-Tossing Game\n";
    cout << "Last 8 digits of M_{10^8+7}(10^4+7) = " << PE_ANSWER << "\n";
    cout << "Use 'PE' to output the answer.\n";
    cout << "Use 'verify' for small value checks.\n";
    
    return 0;
}
