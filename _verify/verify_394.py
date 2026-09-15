#!/usr/bin/env python3
"""PE 394: Eating Pie - Expected number of repeats
Jeff eats pie: F = 1/x. While remaining ≥ F:
- Pick two random points on remaining arc boundary
- Take first two pieces CCW from initial cut, leave third
- Remaining arc length: L_new = L - max(u,v) where u,v ~ U[0,L]

E(x) = expected number of repeats with F=1/x.
Integral equation: f(L) = 1 + (2/L^2)∫_0^L f(t)(L-t)dt for L≥F, f(L)=0 for L<F.
This reduces to ODE: L^2 f'' + 4L f' = 2
Solution: f(L) = (2/3)ln(L) - C/(3L^3) + D
With boundary f(F)=1, f'(F) from continuity.
"""
import sys
import math

def solve_E(x, num_points=10000):
    """Solve E(x) using numerical integration (discretization)"""
    F = 1.0 / x
    
    # Discretize [0, 1] into N points
    N = num_points
    h = 1.0 / N
    
    # f[i] = f(i*h) for i*h >= F, 0 otherwise
    f = [0.0] * (N + 1)
    
    # Start index: first point >= F
    start = int(math.ceil(F / h))
    
    # For each L from F to 1, compute f(L)
    for i in range(start, N + 1):
        L = i * h
        # f(L) = 1 + (2/L^2) * integral_0^L f(t)(L-t) dt
        # Use trapezoidal rule for the integral
        integral = 0.0
        for j in range(1, i):
            t = j * h
            integral += f[j] * (L - t) * h
        # Add half of endpoints
        integral += 0.5 * f[0] * L * h  # f(0)=0
        integral += 0.5 * f[i] * 0 * h  # f(L)*(L-L)=0
        
        # f(L) = 1 + (2/L^2) * integral
        # But f[i] appears on both sides (in integral via trapezoidal)
        # Actually f[i] * 0 = 0, so no self-reference
        f[i] = 1.0 + (2.0 / (L * L)) * integral
    
    return f[N]  # f(1)

def solve_E_analytic(x):
    """Solve using analytic ODE solution"""
    F = 1.0 / x
    
    # f(L) = (2/3)ln(L) + C/L^3 + D  (note sign convention may differ)
    # Actually from ODE: f'(L) = 2/(3L) + C/L^4
    # f(L) = (2/3)ln(L) - C/(3L^3) + D
    #
    # Boundary: f(F) = 1 (from integral equation at L=F)
    # And f(L) continuous with f(L)=0 for L<F.
    # But f(F) should satisfy the integral equation:
    # f(F) = 1 + (2/F^2)∫_0^F f(t)(F-t)dt = 1 + 0 = 1
    #
    # We also need f(L) → 0 as L → 0... but f is only defined for L≥F.
    # For L<F, f=0. At L=F, f jumps from 0 to 1.
    #
    # Looking at the integral equation more carefully at L=F:
    # f(F) = 1 + (2/F^2)∫_0^F f(t)(F-t)dt
    # For t<F, f(t)=0, so integral over [0,F] is 0 + contribution from t=F (measure 0).
    # So f(F) = 1. ✓
    #
    # We need another condition. Differentiating the integral equation:
    # f'(L) = (d/dL)[1 + (2/L^2)∫_0^L f(t)(L-t)dt]
    # Let I(L) = ∫_0^L f(t)(L-t)dt = L∫_0^L f(t)dt - ∫_0^L tf(t)dt
    # I'(L) = ∫_0^L f(t)dt + L*f(L) - L*f(L) = ∫_0^L f(t)dt
    #
    # So f'(L) = (-4/L^3) I(L) + (2/L^2) I'(L)
    # At L=F: I(F) = 0, I'(F) = ∫_0^F f(t)dt = 0 (since f=0 on [0,F))
    # So f'(F) = 0? But from ODE: f'(F) = 2/(3F) + C/F^4.
    # Setting f'(F) = 0: C = -2F^3/3
    #
    # Then: f(F) = (2/3)ln(F) - (-2F^3/3)/(3F^3) + D
    #           = (2/3)ln(F) + 2/9 + D = 1
    # So D = 1 - (2/3)ln(F) - 2/9
    #
    # Let me verify: f(L) = (2/3)ln(L) + (2F^3/3)/(3L^3) + 1 - (2/3)ln(F) - 2/9
    #                    = (2/3)ln(L/F) + 2F^3/(9L^3) + 7/9
    
    ln_F = math.log(F)
    # f(L) = (2/3)ln(L/F) + 2*F^3/(9*L^3) + 7/9
    # At L=1: f(1) = (2/3)ln(1/F) + 2F^3/9 + 7/9
    #               = -(2/3)ln(F) + 2F^3/9 + 7/9
    
    result = -(2/3) * math.log(F) + 2 * F**3 / 9 + 7/9
    return result

if __name__ == '__main__':
    print("Testing PE 394...")
    
    # Test cases
    for x in [1, 2, 7.5]:
        analytic = solve_E_analytic(x)
        print(f"E({x}) = {analytic:.10f}")
    
    # Expected values (from PE)
    print(f"\nE(1) expected: 1")
    print(f"E(2) expected: ~1.2676536759")  
    print(f"E(7.5) expected: ~2.1215732071")
    
    # PE answer
    result = solve_E_analytic(40)
    print(f"\nE(40) = {result:.10f}")
    print(f"Expected: 3.2370342194")
