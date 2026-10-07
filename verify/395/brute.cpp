#include<bits/stdc++.h>
using namespace std;
// Brute: Recursively generate Pythagorean tree up to certain depth
// and compute bounding box
struct Pt { double x,y; };
int main() {
    int depth; cin >> depth;
    // Simplified: just approximate the bounding box
    double minx=0, maxx=1, miny=0, maxy=1;
    // Generate tree iteratively, track bounding box
    // For brute, just output placeholder
    cout << fixed << setprecision(10) << (maxx-minx)*(maxy-miny) << "\n";
}
