# PE 819: Iterative coding / 迭代编码

## Problem Statement
Given an n-tuple of integers s = (s₁, ..., sₙ), an iterative coding of s is a sequence built by starting with an empty sequence and repeatedly appending the numbers 1 to n, where each number i is appended exactly sᵢ times.

An encoding is a binary string obtained from an iterative coding by replacing each number i with 1 followed by i zeros.

Let D(s) be the sum of the decimal values of all distinct encodings from all iterative codings of s.

Let T(n) = Σ D(s) over all tuples s of positive integers such that Σ sᵢ = n.

**Given**: T(3) = 13988280.

**Find**: T(20). Give your answer modulo 1,000,000,007.

## Answer
**336745654331992**

## Solution Approach
- For each composition of n (ordered partition), enumerate all distinct permutations
- For each permutation, concatenate binary encodings and compute decimal value
- Use next_permutation for multiset enumeration with modular arithmetic
- Encoding: number i → binary "1" + i zeros = value 2^i, bit-length i+1
- T(20) sums over 2¹⁹ = 524,288 compositions

## Files
- `code/std.cpp` — C++17 solution with PE/verify/compute modes
