#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// Brute force for PE562: enumerate all lattice triangles with vertices
// in the disk of radius r, find the one with max perimeter,
// compute circumradius R, output round(R/r).

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

int main() {
    ll r;
    cin >> r;
    
    double bestR_over_r = 0;
    
    // Enumerate all triples of lattice points in the disk
    vector<pair<ll,ll>> pts;
    for (ll x = -r; x <= r; x++)
        for (ll y = -r; y <= r; y++)
            if (x*x + y*y <= r*r)
                pts.push_back({x, y});
    
    ll np = pts.size();
    for (ll i = 0; i < np && i < 300; i++) {
        for (ll j = i+1; j < np && j < 500; j++) {
            for (ll k = j+1; k < np && k < 700; k++) {
                ll x1=pts[i].first, y1=pts[i].second;
                ll x2=pts[j].first, y2=pts[j].second;
                ll x3=pts[k].first, y3=pts[k].second;
                
                // Check no interior lattice points (use Pick: A = I + B/2 - 1, I=0)
                // Edge lattice points: gcd of each edge
                ll b1 = gcd(abs(x2-x1), abs(y2-y1));
                ll b2 = gcd(abs(x3-x2), abs(y3-y2));
                ll b3 = gcd(abs(x1-x3), abs(y1-y3));
                if (b1 != 1 || b2 != 1 || b3 != 1) continue; // need primitive edges
                
                // Area via cross product
                ll area2 = abs((x2-x1)*(y3-y1) - (x3-x1)*(y2-y1));
                if (area2 != 1) continue; // area = 1/2
                
                // Side length squares
                ll a2 = (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1);
                ll b2_edge = gcd(abs(x3-x2), abs(y3-y2));
                ll c2 = (x1-x3)*(x1-x3) + (y1-y3)*(y1-y3);
                
                // Perimeter
                double perim = sqrt(a2) + sqrt(b2) + sqrt(c2);
                
                // Circumradius: R = abc/(4A), A=1/2, so R = abc/2
                double R = sqrt((double)a2) * sqrt((double)b2) * sqrt((double)c2) / 2.0;
                double T = R / r;
                
                // Track best perimeter
                static double best_perim = 0;
                if (perim > best_perim) {
                    best_perim = perim;
                    bestR_over_r = T;
                }
            }
        }
    }
    
    cout << (ll)round(bestR_over_r) << "\n";
    return 0;
}
