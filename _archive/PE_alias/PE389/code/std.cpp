#include<bits/stdc++.h>
using namespace std;

// PE389: Platonic Dice - variance of I
// T ~ Uniform(1,4), C = sum of T dice(1,6), O = sum of C dice(1,8),
// D = sum of O dice(1,12), I = sum of D dice(1,20)
// Compute Var(I) = E[I²] - E[I]²
// Use Law of Total Expectation/Variance iteratively

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // For one die with f faces: E = (f+1)/2, Var = (f²-1)/12
    // Let μ_f = (f+1)/2, σ²_f = (f²-1)/12
    
    // Step 1: T ~ d4
    double E_T = 2.5;       // (4+1)/2
    double Var_T = 1.25;    // (16-1)/12 = 15/12
    
    // Step 2: C ~ sum of T d6 dice
    // E[C] = E[E[C|T]] = E[T * μ_6] = E[T] * 3.5 = 2.5 * 3.5
    double E_C = E_T * 3.5;
    // Var(C) = E[Var(C|T)] + Var(E[C|T]) = E[T * σ²_6] + Var(T * μ_6)
    // = E[T] * (35/12) + μ_6² * Var(T) = 2.5 * 35/12 + 3.5² * 1.25
    double Var_C = E_T * (35.0/12.0) + 3.5 * 3.5 * Var_T;
    
    // Step 3: O ~ sum of C d8 dice
    double E_O = E_C * 4.5;
    double Var_O = E_C * (63.0/12.0) + 4.5 * 4.5 * Var_C;
    
    // Step 4: D ~ sum of O d12 dice
    double E_D = E_O * 6.5;
    double Var_D = E_O * (143.0/12.0) + 6.5 * 6.5 * Var_O;
    
    // Step 5: I ~ sum of D d20 dice
    double E_I = E_D * 10.5;
    double Var_I = E_D * (399.0/12.0) + 10.5 * 10.5 * Var_D;
    
    cout << fixed << setprecision(4) << Var_I << "\n";
    return 0;
}
