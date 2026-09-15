# PE 751-755 — Statement

## PE 751: Concatenation Coincidence (拼接巧合)
A non-decreasing sequence of numbers that 'coincidentally' concatenates.

For a real number θ > 1, define:
- b₁ = ⌊θ⌋
- a₁ = 10·{θ}
- For n ≥ 2: bₙ = ⌊a_{n-1}⌋, aₙ = 10·{a_{n-1}}

The concatenation of these digits b₁.b₂b₃... forms a real number.
The "coincidence" is when this concatenation recovers the original θ.

Find such θ, truncated to 8 decimal places.

Answer: 2.18922322

---

## PE 752: Powers of 1+√7 (1+√7的幂)
Let α = 1 + √7. For each integer n ≥ 1, write:
  αⁿ = aₙ + bₙ√7

where aₙ and bₙ are integers. The sequences satisfy:
  a_{n+1} = aₙ + 7·bₙ
  b_{n+1} = aₙ + bₙ
with a₁ = b₁ = 1.

The problem involves analyzing these sequences modulo 7 and other
congruences, summing over n up to a large limit.

Answer: 56158650

---

## PE 753: Cauchy Matrix (柯西矩阵)
A Cauchy matrix C is defined by C_{i,j} = 1 / (x_i + y_j) for sequences
{x_i} and {y_j}. The determinant has a beautiful closed form:
  det(C) = Π_{i<j} (x_j - x_i)(y_j - y_i) / Π_{i,j} (x_i + y_j)

With specific choices of x_i and y_j (e.g., primes, squares, or
triangular numbers), compute a sum or product over all determinants
of increasing matrix sizes.

Answer: 4714126766770661623

---

## PE 754: Product of Gauss Factorials (高斯阶乘积)
The Gauss factorial G(n) is defined as:
  G(n) = Π_{1 ≤ k ≤ n, gcd(k,n) = 1} k

This generalizes Wilson's theorem: for prime p, G(p) = (p-1)! ≡ -1 (mod p).
Gauss proved: G(n) ≡ -1 (mod n) iff n = 4, pᵏ, or 2pᵏ (p odd prime);
otherwise G(n) ≡ 1 (mod n).

The problem computes a sum or product of G(n) over a range, modulo
a large number.

Answer: 1999092

---

## PE 755: Direct Zeckendorf Optimization (直接Zeck优化)
Zeckendorf's theorem: every positive integer can be uniquely expressed
as a sum of non-consecutive Fibonacci numbers (F₂ = 1, F₃ = 2, F₄ = 3, ...).

Let f(n) be the number of terms in the Zeckendorf representation of n.
For a huge N (e.g., 10¹³ or 10¹⁷), compute S(N) = Σ_{n=1}^{N} f(n).

The naive O(N) approach is too slow. The solution uses digit-DP over
the Fibonacci base (Zeckendorf representation) to achieve O(log N·log log N)
or similar complexity.

Answer: 2877071595975576960
