# PE 816: Shortest distance of points / 点间最短距离

## Problem Statement
We create a sequence of points in the Euclidean plane using a pseudo-random generator:

- s₀ = 290797
- s_{k+1} = s_k² mod 50515093
- P_k = (s_{2k}, s_{2k+1})

Let d(k) be the shortest distance of any two distinct points among P₀, ..., P_{k-1}.

**Example**: d(14) = 546446.466846479

**Find**: d(2000000). Give your answer rounded to 9 places after the decimal point.

## Answer
**20.880613018**

## Solution Approach
- Generate 2,000,000 points using the recurrence (offline, O(N))
- Find the closest pair using a sweep-line algorithm in O(N log N)
- Active set maintained as a balanced BST (std::set) ordered by y-coordinate
- Only points within √(best_dist) in x are kept in the active window
- For each new point, query the active set for points within √(best_dist) in y

## Files
- `code/std.cpp` — C++17 solution with PE/verify/compute modes
