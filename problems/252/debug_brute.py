import itertools

def generate_points(N):
    pts = []
    S = 290797
    for i in range(2 * N):
        S = (S * S) % 50515093
        T = (S % 2000) - 1000
        if i % 2 == 0:
            pts.append([T, None])
        else:
            pts[i//2][1] = T
    return pts

def cross(o, a, b):
    return (a[0]-o[0])*(b[1]-o[1]) - (a[1]-o[1])*(b[0]-o[0])

def convex_hull(pts):
    pts = sorted(set((p[0], p[1]) for p in pts))
    if len(pts) <= 1: return pts
    lower = []
    for p in pts:
        while len(lower) >= 2 and cross(lower[-2], lower[-1], p) <= 0:
            lower.pop()
        lower.append(p)
    upper = []
    for p in reversed(pts):
        while len(upper) >= 2 and cross(upper[-2], upper[-1], p) <= 0:
            upper.pop()
        upper.append(p)
    return lower[:-1] + upper[:-1]

def point_in_polygon(p, hull):
    n = len(hull)
    for i in range(n):
        j = (i+1)%n
        if cross(hull[i], hull[j], p) >= 0:
            return False
    return True

def on_segment(p, a, b):
    if cross(a, b, p) != 0: return False
    return min(a[0],b[0]) <= p[0] <= max(a[0],b[0]) and min(a[1],b[1]) <= p[1] <= max(a[1],b[1])

def polygon_area2(hull):
    n = len(hull)
    a2 = 0
    for i in range(n):
        j = (i+1)%n
        a2 += hull[i][0]*hull[j][1] - hull[i][1]*hull[j][0]
    return abs(a2)

pts = generate_points(5)
N = 5
print("Points:", pts)

best = 0
best_hull = None
for mask in range(1, 1<<N):
    if bin(mask).count('1') < 3: continue
    subset = [pts[i] for i in range(N) if mask & (1<<i)]
    hull = convex_hull(subset)
    if len(hull) < 3: continue
    
    empty = True
    for i in range(N):
        if mask & (1<<i): 
            is_vertex = (pts[i][0], pts[i][1]) in hull
            if is_vertex: continue
            on_bdry = False
            for j in range(len(hull)):
                k = (j+1)%len(hull)
                if on_segment((pts[i][0], pts[i][1]), hull[j], hull[k]):
                    on_bdry = True
                    break
            if not on_bdry:
                empty = False
                break
        else:
            if point_in_polygon((pts[i][0], pts[i][1]), hull):
                empty = False
                break
    if empty:
        a2 = polygon_area2(hull)
        if a2 > best:
            best = a2
            best_hull = hull

print(f"Best area: {best/2.0}, hull: {best_hull}")
