#!/usr/bin/env python3
"""PE 957: Point Genesis - exact geometric simulation using homogeneous integer coordinates."""
from math import gcd


def norm3(v):
    g = gcd(gcd(abs(v[0]), abs(v[1])), abs(v[2]))
    if g == 0:
        return v
    # canonical sign
    s = 1
    if v[0] < 0 or (v[0] == 0 and (v[1] < 0 or (v[1] == 0 and v[2] < 0))):
        s = -1
    return (s * v[0] // g, s * v[1] // g, s * v[2] // g)


def cross(a, b):
    return (a[1] * b[2] - a[2] * b[1],
            a[2] * b[0] - a[0] * b[2],
            a[0] * b[1] - a[1] * b[0])


def line_through(p, q):
    return norm3(cross(p, q))


def intersect(l1, l2):
    return norm3(cross(l1, l2))


def pt_key(p):
    return p


# Initial configuration (5 points in general position)
R = [(0, 0, 1), (1, 0, 1), (0, 1, 1)]
B = [(2, 3, 1), (3, 1, 1)]

red = set(R)
blue = set(B)


def simulate(days):
    global blue
    results = []
    for day in range(1, days + 1):
        # all lines through red-blue pairs
        lines = set()
        for r in red:
            for b in blue:
                lines.add(line_through(r, b))
        # pairwise intersections -> new points
        line_list = list(lines)
        newpts = set()
        for i in range(len(line_list)):
            for j in range(i + 1, len(line_list)):
                p = intersect(line_list[i], line_list[j])
                if p[2] == 0:
                    continue  # at infinity
                if p in red or p in blue:
                    continue
                newpts.add(p)
        blue = blue | newpts
        results.append(len(blue))
        print(f"g({day}) = {len(blue)}  (lines={len(lines)}, new={len(newpts)})")
    return results


print("Simulating PE 957...")
res = simulate(4)
print("Done.")
