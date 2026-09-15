#!/usr/bin/env python3
"""PE 389: Platonic Dice - Variance of I
Chain: 1d4 → T, Td6 → C, Cd8 → O, Od12 → D, Dd20 → I
Find variance of I.
Uses law of total variance: Var(Y) = E[Var(Y|X)] + Var(E[Y|X])
"""
import sys

def solve():
    """
    For a fair k-sided die:
    E[single] = (k+1)/2
    Var[single] = (k^2 - 1)/12
    
    For sum of m independent dice:
    E[sum] = m * (k+1)/2
    Var[sum] = m * (k^2 - 1)/12
    """
    # Starting from T
    # T ~ 1d4
    E_T = (4 + 1) / 2         # = 2.5
    Var_T = (4*4 - 1) / 12    # = 15/12 = 1.25
    
    # C = sum of T d6
    E_C_given_T = lambda t: t * (6 + 1) / 2     # t * 3.5
    Var_C_given_T = lambda t: t * (6*6 - 1) / 12  # t * 35/12
    
    E_C = E_T * 3.5  # = 2.5 * 3.5 = 8.75
    Var_C = E_T * (35/12) + Var_T * (3.5**2)  # law of total variance
    # E[Var(C|T)] = E[T * 35/12] = E_T * 35/12
    # Var(E[C|T]) = Var(T * 3.5) = 3.5^2 * Var_T
    Var_C = E_T * (35/12) + Var_T * (3.5**2)
    
    # O = sum of C d8
    E_O_given_C = lambda c: c * (8 + 1) / 2     # c * 4.5
    Var_O_given_C = lambda c: c * (8*8 - 1) / 12  # c * 63/12
    
    E_O = E_C * 4.5
    Var_O = E_C * (63/12) + Var_C * (4.5**2)
    
    # D = sum of O d12
    E_D_given_O = lambda o: o * (12 + 1) / 2      # o * 6.5
    Var_D_given_O = lambda o: o * (12*12 - 1) / 12  # o * 143/12
    
    E_D = E_O * 6.5
    Var_D = E_O * (143/12) + Var_O * (6.5**2)
    
    # I = sum of D d20
    E_I_given_D = lambda d: d * (20 + 1) / 2       # d * 10.5
    Var_I_given_D = lambda d: d * (20*20 - 1) / 12  # d * 399/12
    
    E_I = E_D * 10.5
    Var_I = E_D * (399/12) + Var_D * (10.5**2)
    
    return Var_I

if __name__ == '__main__':
    import math
    result = solve()
    print(f"Variance of I = {result:.10f}")
    print(f"Rounded to 4 decimal places: {result:.4f}")
    expected = 2406376.3623
    print(f"Expected: {expected}")
    
    # Check with tolerance
    assert abs(result - expected) < 0.0001, f"Mismatch: {result:.4f} vs {expected}"
    print("Test passed!")
