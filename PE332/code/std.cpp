#include<bits/stdc++.h>
using namespace std;
#define ll long long
using ld = long double;

#ifndef M_PIl
#define M_PIl 3.141592653589793238462643383279502884L
#endif

// PE332: Spherical Triangles
// Find integer points on sphere of radius r
// Compute minimum area of non-degenerate spherical triangle

struct Point {
    ll x, y, z;
};

// Generate all integer points on sphere x^2+y^2+z^2 = r^2
vector<Point> sphere_points(ll r) {
    vector<Point> pts;
    ll r2 = r*r;
    for (ll x = -r; x <= r; x++) {
        ll x2 = x*x;
        if (x2 > r2) continue;
        for (ll y = -r; y <= r; y++) {
            ll y2 = y*y;
            ll s = x2 + y2;
            if (s > r2) continue;
            ll z2 = r2 - s;
            ll z = (ll)round(sqrt((ld)z2));
            if (z*z == z2) {
                pts.push_back({x, y, z});
                if (z != 0) pts.push_back({x, y, -z});
            }
        }
    }
    // Remove duplicates
    sort(pts.begin(), pts.end(), [](const Point& a, const Point& b) {
        if (a.x != b.x) return a.x < b.x;
        if (a.y != b.y) return a.y < b.y;
        return a.z < b.z;
    });
    pts.erase(unique(pts.begin(), pts.end(), [](const Point& a, const Point& b) {
        return a.x == b.x && a.y == b.y && a.z == b.z;
    }), pts.end());
    return pts;
}

// Cross product
Point cross(const Point& a, const Point& b) {
    return {
        a.y*b.z - a.z*b.y,
        a.z*b.x - a.x*b.z,
        a.x*b.y - a.y*b.x
    };
}

// Dot product
ll dot(const Point& a, const Point& b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

ld len(const Point& a) {
    return sqrtl((ld)(a.x*a.x + a.y*a.y + a.z*a.z));
}

// Check if three points are on the same great circle (coplanar with origin)
bool degenerate(const Point& a, const Point& b, const Point& c) {
    // Triple product (a x b) · c = 0 means coplanar
    Point cp = cross(a, b);
    return dot(cp, c) == 0;
}

// Spherical triangle area on sphere of radius r
// Using spherical excess: Area = (A+B+C-PI) * r^2
ld spherical_area(const Point& p1, const Point& p2, const Point& p3, ld r) {
    // Convert to unit vectors
    ld r_inv = 1.0L / r;
    ld x1 = p1.x * r_inv, y1 = p1.y * r_inv, z1 = p1.z * r_inv;
    ld x2 = p2.x * r_inv, y2 = p2.y * r_inv, z2 = p2.z * r_inv;
    ld x3 = p3.x * r_inv, y3 = p3.y * r_inv, z3 = p3.z * r_inv;
    
    // Normal vectors to the planes through origin containing the edges
    // n1 = p2 x p3 (normalized), n2 = p3 x p1, n3 = p1 x p2
    auto cross_norm = [](ld ax, ld ay, ld az, ld bx, ld by, ld bz) {
        ld cx = ay*bz - az*by;
        ld cy = az*bx - ax*bz;
        ld cz = ax*by - ay*bx;
        ld len_c = sqrtl(cx*cx + cy*cy + cz*cz);
        return make_tuple(cx/len_c, cy/len_c, cz/len_c);
    };
    
    auto [nx1, ny1, nz1] = cross_norm(x2, y2, z2, x3, y3, z3);
    auto [nx2, ny2, nz2] = cross_norm(x3, y3, z3, x1, y1, z1);
    auto [nx3, ny3, nz3] = cross_norm(x1, y1, z1, x2, y2, z2);
    
    // Angle at vertex 1: PI - angle between n2 and n3
    ld dot_n2_n3 = nx2*nx3 + ny2*ny3 + nz2*nz3;
    dot_n2_n3 = max(-1.0L, min(1.0L, dot_n2_n3));
    ld A = acosl(-dot_n2_n3);
    
    ld dot_n3_n1 = nx3*nx1 + ny3*ny1 + nz3*nz1;
    dot_n3_n1 = max(-1.0L, min(1.0L, dot_n3_n1));
    ld B = acosl(-dot_n3_n1);
    
    ld dot_n1_n2 = nx1*nx2 + ny1*ny2 + nz1*nz2;
    dot_n1_n2 = max(-1.0L, min(1.0L, dot_n1_n2));
    ld C = acosl(-dot_n1_n2);
    
    ld area = (A + B + C - M_PIl) * r * r;
    return area;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(6);
    
    int R;
    cin >> R;
    
    ld total = 0.0L;
    
    for (int rad = 1; rad <= R; rad++) {
        auto pts = sphere_points(rad);
        int n = (int)pts.size();
        
        if (n < 3) continue;  // Need at least 3 points for a triangle
        
        ld min_area = 1e30L;
        bool found = false;
        
        for (int i = 0; i < n; i++) {
            for (int j = i+1; j < n; j++) {
                if (degenerate(pts[i], pts[j], pts[j])) continue;  // same point check (won't happen)
                for (int k = j+1; k < n; k++) {
                    if (degenerate(pts[i], pts[j], pts[k])) continue;
                    
                    ld area = spherical_area(pts[i], pts[j], pts[k], rad);
                    if (area < min_area) {
                        min_area = area;
                        found = true;
                    }
                }
            }
        }
        
        if (found) total += min_area;
    }
    
    cout << total << "\n";
    
    return 0;
}
