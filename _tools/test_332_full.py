"""PE 332: Full computation for r=1..50"""
import math

def integer_points_on_sphere(r):
    points = []
    r2 = r * r
    max_xy = int(math.isqrt(r2))
    for x in range(-max_xy, max_xy + 1):
        x2 = x * x
        if x2 > r2: continue
        max_y = int(math.isqrt(r2 - x2))
        for y in range(-max_y, max_y + 1):
            y2 = y * y
            s = x2 + y2
            if s > r2: continue
            z2 = r2 - s
            z = int(math.isqrt(z2))
            if z * z == z2:
                if z == 0:
                    points.append((x, y, 0))
                else:
                    points.append((x, y, z))
                    points.append((x, y, -z))
                break
    return list(set(points))

def spherical_area(v1, v2, v3, r):
    u1 = (v1[0]/r, v1[1]/r, v1[2]/r)
    u2 = (v2[0]/r, v2[1]/r, v2[2]/r)
    u3 = (v3[0]/r, v3[1]/r, v3[2]/r)
    
    def dot(a, b):
        return a[0]*b[0] + a[1]*b[1] + a[2]*b[2]
    
    det = (v1[0]*(v2[1]*v3[2] - v2[2]*v3[1]) -
           v1[1]*(v2[0]*v3[2] - v2[2]*v3[0]) +
           v1[2]*(v2[0]*v3[1] - v2[1]*v3[0]))
    if det == 0:
        return None
    
    cos_a = max(-1.0, min(1.0, dot(u2, u3)))
    cos_b = max(-1.0, min(1.0, dot(u1, u3)))
    cos_c = max(-1.0, min(1.0, dot(u1, u2)))
    
    sin_a = math.sqrt(max(0, 1 - cos_a*cos_a))
    sin_b = math.sqrt(max(0, 1 - cos_b*cos_b))
    sin_c = math.sqrt(max(0, 1 - cos_c*cos_c))
    
    if sin_a < 1e-14 or sin_b < 1e-14 or sin_c < 1e-14:
        return None
    
    cos_A = max(-1.0, min(1.0, (cos_a - cos_b * cos_c) / (sin_b * sin_c)))
    cos_B = max(-1.0, min(1.0, (cos_b - cos_a * cos_c) / (sin_a * sin_c)))
    cos_C = max(-1.0, min(1.0, (cos_c - cos_a * cos_b) / (sin_a * sin_b)))
    
    A = math.acos(cos_A)
    B = math.acos(cos_B)
    C = math.acos(cos_C)
    
    spherical_excess = A + B + C - math.pi
    return spherical_excess * r * r

def min_area_for_r(r):
    points = integer_points_on_sphere(r)
    n = len(points)
    if n < 3:
        return None
    
    min_area = float('inf')
    for i in range(n):
        for j in range(i+1, n):
            for k in range(j+1, n):
                area = spherical_area(points[i], points[j], points[k], r)
                if area is not None and area > 1e-14:
                    if area < min_area:
                        min_area = area
    return min_area if min_area < float('inf') else None

import sys
sys.setrecursionlimit(10000)

total = 0.0
for r in range(1, 51):
    A = min_area_for_r(r)
    if A is not None:
        total += A
        print(f"r={r:2d}: A={A:.6f}, running_total={total:.6f}")
    else:
        print(f"r={r:2d}: no triangles")

print(f"\nTotal sum: {total:.6f}")
