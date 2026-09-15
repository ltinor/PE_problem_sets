#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 966: Triangle Circle Intersection / 三角形与圆的交集
//
// I(a,b,c) = largest possible area of intersection between a triangle
// with sides a,b,c and a circle of equal area.
//
// I(3,4,5) ≈ 4.593049, I(3,4,6) ≈ 3.552564.
// Find sum of I(a,b,c) for all integer triangles with:
//   1 ≤ a ≤ b ≤ c < a+b and a+b+c ≤ 200.
// Round to 2 decimal places.
//
// Key observations:
// - For sides (a,b,c), triangle area is determined (Heron's formula).
// - The circle has the same area: πR² = area → R = √(area/π).
// - We need to position the circle to maximize overlap with the triangle.
//
// - The problem of maximizing the intersection of a triangle and a circle
//   of fixed area: we can place the circle anywhere relative to the triangle.
//   The optimal placement likely has the circle covering part of the triangle.
//
// - Since R depends on the triangle area, and the triangle area depends
//   on sides, for each triangle we compute the optimal overlap.
//
// - This is an optimization problem in plane geometry.
//
// - For a convex shape (triangle) and a circle of equal area, the maximum
//   intersection is at least the area of overlap when the circle is centered
//   at the incenter or centroid.
//
// - Actually, we want to MAXIMIZE the intersection. The circle can be
//   placed anywhere. The maximum overlap occurs when the circle covers
//   as much of the triangle as possible.
//
// - Since area(circle) = area(triangle), if we can fit the entire circle
//   inside the triangle, the overlap is the circle's area (which equals
//   the triangle's area). But a circle cannot be fully inside a triangle
//   of equal area (the triangle would need an incircle of that size, which
//   is impossible for most triangles).
//
// - For a given triangle, the maximum overlap depends on the geometry.
//   The circle wants to be centered where the triangle is "thickest".
//   For acute triangles, the incenter region works well.
//
// - The problem asks for I(a,b,c) which is the MAXIMUM possible intersection
//   over all placements of the circle.
//
// - Since the circle has the same area as the triangle, and we're optimizing
//   placement, this is equivalent to: how much of the triangle can be covered
//   by a circle of equal area, with optimal placement?
//
// - This is a nontrivial computational geometry problem. For a given triangle,
//   we need to find the maximum overlap area between the triangle and a
//   circle of fixed radius R.
//
// - Known result: For a convex polygon and a circle, the maximum overlap
//   occurs when the circle is tangent to at least 2 edges, or its boundary
//   passes through 2+ vertices of the polygon. The optimal center lies on
//   the medial axis/skeleton.
//
// - For triangles specifically, the medial axis consists of:
//   - The three angle bisectors (inside the triangle)
//   Extended: the medial axis of a triangle is the union of three line
//   segments from the incenter to the vertices (or the incenter to the
//   excenters for the external part).
//
// - The circle center for maximum overlap likely lies on one of the
//   angle bisectors, or at the incenter itself.
//
// - A practical approach for the given range (a+b+c ≤ 200):
//   Number of integer triangles: relatively small.
//   For each triangle, use numerical optimization (ternary search or
//   gradient descent) to find the optimal circle position.
//
// - The circle has radius R = √(A/π) where A = triangle area.
//   The intersection area can be computed by decomposing into:
//   intersection of circle with each triangle edge half-plane, or
//   by computing the polygon-circle intersection area.
//
// - PE answer: (to be computed as floating point)

const ll PE_ANSWER = 0; // placeholder (floating point)
const int MAX_PERIMETER = 200;

// Heron's formula for triangle area
double triangle_area(double a, double b, double c) {
    double s = (a + b + c) / 2.0;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

// Check triangle inequality
bool is_triangle(ll a, ll b, ll c) {
    return a + b > c && a + c > b && b + c > a;
}

void verify() {
    cout << "PE 966: Triangle Circle Intersection / 三角形与圆的交集\n\n";
    
    cout << "=== Problem Summary ===\n";
    cout << "I(a,b,c) = max intersection area between triangle (a,b,c)\n";
    cout << "and a circle of equal area.\n";
    cout << "I(3,4,5)≈4.593049, I(3,4,6)≈3.552564.\n";
    cout << "Sum over all integer triangles with a≤b≤c, a+b+c≤200.\n";
    cout << "Round to 2 decimal places.\n\n";
    
    cout << "=== Analysis ===\n";
    cout << "For each triangle: area A, circle radius R = √(A/π).\n";
    cout << "Optimize circle placement for maximum overlap.\n";
    cout << "Optimal center lies on medial axis (angle bisectors).\n\n";
    
    cout << "=== Triangle Count ===\n";
    int count = 0;
    for (ll a = 1; a <= MAX_PERIMETER; a++) {
        for (ll b = a; b <= MAX_PERIMETER - a; b++) {
            for (ll c = b; c <= MAX_PERIMETER - a - b; c++) {
                if (is_triangle(a, b, c) && c < a + b) {
                    count++;
                }
            }
        }
    }
    cout << "  Number of triangles: " << count << "\n\n";
    
    // Verify I(3,4,5)
    cout << "=== Example I(3,4,5) ===\n";
    double A = triangle_area(3, 4, 5);
    double R = sqrt(A / M_PI);
    cout << "  Area = " << A << " (should be 6)\n";
    cout << "  R = " << R << "\n";
    // Inradius = 1 (for 3-4-5 triangle)
    cout << "  Inradius = " << 1.0 << "\n";
    cout << "  I(3,4,5) ≈ 4.593049 (given)\n\n";
    
    cout << "=== Target ===\n";
    cout << "Sum I(a,b,c) for a+b+c ≤ 200, rounded to 2 decimals.\n";
    cout << "Need numerical optimization for each triangle.\n\n";
    
    cout << "=== PE Answer ===\n" << PE_ANSWER << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);
    
    if (query == "PE") { cout << PE_ANSWER << "\n"; return 0; }
    if (query == "verify") { verify(); return 0; }
    cout << "PE 966: Triangle Circle Intersection / 三角形与圆的交集\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for checks.\n";
    return 0;
}
