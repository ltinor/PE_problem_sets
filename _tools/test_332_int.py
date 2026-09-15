"""PE 332 Adapted: Brute force search for integer areas"""
import math

# cos A = cos a / (1 + cos a)
# Area = 3*acos(cos A) - pi

# Search for a values that give integer area
# Area ranges from 0 to 4*pi ≈ 12.566

results = []
# Try a from 0.0001 to pi-0.0001 in small steps
step = 0.00001
a = step
while a < math.pi - step:
    cos_a = math.cos(a)
    cos_A = cos_a / (1 + cos_a)
    if abs(cos_A) <= 1:
        A = math.acos(max(-1.0, min(1.0, cos_A)))
        area = 3*A - math.pi
        # Check if area is very close to integer
        rounded = round(area)
        if abs(area - rounded) < 1e-8 and rounded >= 1:
            results.append((a, area, rounded))
    a += step
    if len(results) >= 20:
        break

print("Close-to-integer areas found:")
for a, area, rounded in results:
    print(f"  a={a:.10f} rad ({math.degrees(a):.4f}°), area={area:.10f} ≈ {rounded}")

# Let me also try precise search: solve cos a/(1+cos a) = cos((pi+n)/3) for each n

print("\nPrecise solutions for integer area n:")
for n in range(1, 13):
    # For area = n: 3A - pi = n → A = (pi + n)/3
    A = (math.pi + n) / 3
    cos_A = math.cos(A)
    # cos a = cos_A / (1 - cos_A) 
    if 1 - cos_A == 0:
        print(f"  n={n}: division by zero, skip")
        continue
    cos_a = cos_A / (1 - cos_A)
    if abs(cos_a) <= 1:
        a = math.acos(cos_a)
        area_check = 3 * math.acos(math.cos(a)/(1+math.cos(a))) - math.pi
        print(f"  n={n}: a={a:.10f} rad ({math.degrees(a):.4f}°), cos_a={cos_a:.10f}, area_check={area_check:.10f}")

# Sum of integer areas from 1 to 12:
print(f"\nSum 1..12 = {sum(range(1,13))}")
