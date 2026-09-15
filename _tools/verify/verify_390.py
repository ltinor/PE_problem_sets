#!/usr/bin/env python3
"""PE 390: Triangles with non rational sides and integral area
Sides: sqrt(1+b^2), sqrt(1+c^2), sqrt(b^2+c^2)
Area = sqrt(b^2 + c^2 + b^2*c^2) / 2

Key insight: For odd b, d^2 = b^2 + c^2 + b^2c^2 ≡ 1 (mod 8) when c even,
or ≡ 3 (mod 8) when c odd. Neither gives d even. So only even b contribute.

For b=2k: d^2 - (4k^2+1)c^2 = 4k^2 (Pell equation)
All solutions from class (2k, 0) with fundamental unit (8k^2+1, 4k).
d always even, so area = d/2 always integer.
"""
import sys

def S(n):
    total = 0
    k = 1  # b = 2k
    while True:
        b = 2 * k
        D = b * b + 1  # = 4k^2 + 1
        N = b * b       # = 4k^2
        
        # Fundamental unit: x^2 - D*y^2 = 1
        x_f = 2 * N + 1  # = 8k^2 + 1
        y_f = b           # = 2k, wait: 2*b = 4k? Let me recheck.
        # For D = b^2+1: fundamental solution is (2b^2+1, 2b)
        # b = 2k: x_f = 2*(4k^2)+1 = 8k^2+1, y_f = 2*(2k) = 4k
        x_f = 8 * k * k + 1
        y_f = 4 * k
        
        # Start from particular solution (d_0, c_0) = (b, 0)
        d, c = b, 0
        found = False
        
        while True:
            d_new = x_f * d + D * y_f * c
            c_new = y_f * d + x_f * c
            d, c = d_new, c_new
            
            area = d // 2
            if area > n:
                break
            if c > 0 and c >= b:
                total += area
                found = True
        
        if not found:
            # First area for this k: area_1 = d_1/2 = b*(2b^2+1)/2 = k*(8k^2+1)
            first_area = k * (8 * k * k + 1)
            if first_area > n:
                break
        
        k += 1
    
    return total

if __name__ == '__main__':
    print("Testing PE 390...")
    
    for test_n in [10, 100, 1000, 10000, 100000]:
        result = S(test_n)
        print(f"S({test_n}) = {result}")
    
    result = S(10**6)
    print(f"S(10^6) = {result}")
    expected = 18018206
    assert result == expected, f"Mismatch: {result} vs {expected}"
    print("Test passed!")
