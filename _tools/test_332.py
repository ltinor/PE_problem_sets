"""PE 332: Spherical triangles - compute smallest area for r=1..50"""
import math
from itertools import combinations

def integer_points_on_sphere(r):
    """Return list of integer triples (x,y,z) with x²+y²+z²=r²"""
    points = []
    r2 = r * r
    max_xy = int(math.isqrt(r2))
    for x in range(-max_xy, max_xy + 1):
        x2 = x * x
        if x2 > r2:
            continue
        max_y = int(math.isqrt(r2 - x2))
        for y in range(-max_y, max_y + 1):
            y2 = y * y
            if x2 + y2 > r2:
                continue
            z2 = r2 - x2 - y2
            z = int(math.isqrt(z2))
            if z * z == z2:
                points.append((x, y, z))
                if z != 0:
                    points.append((x, y, -z))
                break  # only one z (or ±z) per (x,y)
    # Deduplicate
    return list(set(points))

def spherical_area(v1, v2, v3, r):
    """Area of spherical triangle on sphere of radius r with vertices v1,v2,v3"""
    # Normalize
    u1 = (v1[0]/r, v1[1]/r, v1[2]/r)
    u2 = (v2[0]/r, v2[1]/r, v2[2]/r)
    u3 = (v3[0]/r, v3[1]/r, v3[2]/r)
    
    def dot(a, b):
        return a[0]*b[0] + a[1]*b[1] + a[2]*b[2]
    
    def cross(a, b):
        return (a[1]*b[2] - a[2]*b[1],
                a[2]*b[0] - a[0]*b[2],
                a[0]*b[1] - a[1]*b[0])
    
    def norm(v):
        return math.sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2])
    
    # Check non-degenerate (not coplanar with origin)
    det = (v1[0]*(v2[1]*v3[2] - v2[2]*v3[1]) -
           v1[1]*(v2[0]*v3[2] - v2[2]*v3[0]) +
           v1[2]*(v2[0]*v3[1] - v2[1]*v3[0]))
    if abs(det) < 1e-12:
        return None  # degenerate
    
    # Compute angles using spherical law of cosines
    cos_a = dot(u2, u3)
    cos_b = dot(u1, u3)
    cos_c = dot(u1, u2)
    
    # Clamp to [-1, 1]
    cos_a = max(-1.0, min(1.0, cos_a))
    cos_b = max(-1.0, min(1.0, cos_b))
    cos_c = max(-1.0, min(1.0, cos_c))
    
    sin_a = math.sqrt(1 - cos_a*cos_a)
    sin_b = math.sqrt(1 - cos_b*cos_b)
    sin_c = math.sqrt(1 - cos_c*cos_c)
    
    if sin_a < 1e-12 or sin_b < 1e-12 or sin_c < 1e-12:
        return None  # degenerate (two points same or antipodal)
    
    cos_A = (cos_a - cos_b * cos_c) / (sin_b * sin_c)
    cos_B = (cos_b - cos_a * cos_c) / (sin_a * sin_c)
    cos_C = (cos_c - cos_a * cos_b) / (sin_a * sin_b)
    
    cos_A = max(-1.0, min(1.0, cos_A))
    cos_B = max(-1.0, min(1.0, cos_B))
    cos_C = max(-1.0, min(1.0, cos_C))
    
    A = math.acos(cos_A)
    B = math.acos(cos_B)
    C = math.acos(cos_C)
    
    spherical_excess = A + B + C - math.pi
    area = spherical_excess * r * r
    
    return area

def compute_A(r):
    """Minimum spherical triangle area for given r"""
    points = integer_points_on_sphere(r)
    n = len(points)
    if n < 3:
        return None  # not enough points
    
    min_area = float('inf')
    for i in range(n):
        for j in range(i+1, n):
            for k in range(j+1, n):
                area = spherical_area(points[i], points[j], points[k], r)
                if area is not None and area > 1e-12:
                    if area < min_area:
                        min_area = area
    
    if min_area == float('inf'):
        return None
    return min_area

# Test for small r
print("Testing A(r) for small r:")
for r in range(1, 21):
    A = compute_A(r)
    if A is not None:
        print(f"r={r}: A(r) = {A:.6f}")
    else:
        print(f"r={r}: no valid triangles")

# Given: A(14) ≈ 3.294040
print(f"\nVerification: A(14) = {compute_A(14):.6f} (expected 3.294040)")
