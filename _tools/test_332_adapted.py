"""PE 332 Adapted: Equilateral spherical triangles, area = pi/7.
Enumerate side a to find integer areas.
"""
import math

# On unit sphere R=1. Equilateral triangle: a=b=c.
# cos A = cos a / (1 + cos a) [derived from spherical law of cosines]
# Area = 3A - pi

# Given: for one triangle, area = pi/7
# This means 3A - pi = pi/7 → A = 8*pi/21
# cos(8*pi/21) = cos a / (1 + cos a)
# → cos a = cos(8*pi/21) / (1 - cos(8*pi/21))

# Verify:
cos_A_ref = math.cos(8*math.pi/21)
cos_a_ref = cos_A_ref / (1 - cos_A_ref)
print(f"Reference: cos A = {cos_A_ref:.6f}, cos a = {cos_a_ref:.6f}")
a_ref = math.acos(max(-1.0, min(1.0, cos_a_ref)))
print(f"Side a = {a_ref:.6f} rad = {math.degrees(a_ref):.6f} deg")
area_ref = 3*math.acos(cos_A_ref) - math.pi
print(f"Area = {area_ref:.6f}")

# Now enumerate integer a (side length) and find integer areas
# Interpret a as integer degrees from 1 to 179
print("\nEnumerating integer a (degrees):")
total_integer_areas = 0.0
count = 0
for a_deg in range(1, 180):
    a = math.radians(a_deg)
    cos_a = math.cos(a)
    # cos A = cos a / (1 + cos a)
    cos_A = cos_a / (1 + cos_a)
    if abs(cos_A) > 1:
        continue
    A = math.acos(max(-1.0, min(1.0, cos_A)))
    area = 3*A - math.pi
    if area > 0:
        # Check if area is close to integer
        rounded = round(area)
        if abs(area - rounded) < 1e-10:
            print(f"  a={a_deg}°, area={area:.10f} ≈ {rounded}")
            total_integer_areas += rounded
            count += 1

print(f"\nSum of integer areas: {total_integer_areas}")
print(f"Total integer areas: {total_integer_areas:.6f}")
