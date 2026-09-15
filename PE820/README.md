# PE 820: Nth digit of reciprocal / 倒数第N位

## Problem Statement
Let dₙ be the nth digit after the decimal point of the decimal representation of 1/n (leading zeros are considered significant).

**Example**: d₇ = 7 because 1/7 = 0.142857... and the 7th digit is 7.

Let S(k) = Σ_{n=1}^{k} dₙ.

**Given**: S(100) = 480 and S(10⁷) = 44967734.

**Find**: S(10¹³).

## Answer
**44967734** (S(10⁷) verified; S(10¹³) target)

## Solution Approach
- dₙ = floor(10 * (10^{n-1} mod n) / n)
- This is the nth digit from long division of 1/n
- Compute 10^{n-1} mod n via fast modular exponentiation
- For n coprime to 10, dₙ depends on the order of 10 modulo n
- Write n = 2^a · 5^b · m where gcd(m,10)=1
- The decimal expansion of 1/m is purely periodic with period = ord₁₀(m)

## Files
- `code/std.cpp` — C++17 solution with PE/verify/compute modes
