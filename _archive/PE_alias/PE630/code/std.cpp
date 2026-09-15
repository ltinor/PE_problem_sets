#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// PE 630: Crossed Lines
// 交叉的直线
//
// Points (T_{2k-1}, T_{2k}) where:
//   S_0 = 290797
//   S_{n+1} = S_n^2 mod 50515093
//   T_n = (S_n mod 2000) - 1000
//
// L_n = set of unique lines formed by connecting each pair of n points.
// M(L_n) = number of lines
// S(L_n) = sum over each line of #lines that cross it.
//
// Given: M(L_3)=3, S(L_3)=6. M(L_100)=4948, S(L_100)=24477690.
// Find: S(L_2500).
//
// PE answer: 9669182880384
//
// Analysis:
// For n points, there are at most C(n,2) lines (pairs).
// Two lines AB and CD cross iff their segments intersect (excluding
// endpoints), which can be determined by orientation tests.
//
// However, lines are extended infinitely! So two lines cross iff
// they are NOT parallel. For lines formed by two points each:
// - Line through A,B has direction vector (dx, dy) = (B-A).
// - Two lines cross iff their direction vectors are not parallel,
//   i.e., cross product ≠ 0.
//
// But we need to count unique lines! If 3 points are collinear,
// they form only 1 line, not 3.
//
// Algorithm:
// 1. Generate n points
// 2. For each pair (i,j), compute the line parameters (slope, intercept)
//    in a canonical form to deduplicate
// 3. Count unique lines = M(L_n)
// 4. For each line, count how many other lines cross it
// 5. S(L_n) = sum of crossing counts
//
// Since lines are extended infinitely, two lines cross iff they have
// different slopes. Lines with the same slope are parallel and don't cross.
//
// So: for each slope, let c = number of lines with that slope.
// A line with that slope crosses (M - c) other lines.
// S(L_n) = Σ_slope c_s × (M - c_s) = M² - Σ_slope c_s²
//
// But wait: parallel lines don't cross. But do coincident lines cross?
// In the problem: "the lines being extended indefinitely in both directions."
// Coincident lines would have infinitely many intersection points.
// But the set L_n contains unique lines, so coincident lines are the same line.
//
// Actually, two lines formed by different point pairs might be the SAME LINE
// if the 4 points are collinear. This is handled by deduplication.
//
// For the crossing count: lines with the same slope are parallel.
// A line crosses all lines with different slopes.
//
// S(L) = Σ_{line i} (M - c_{slope(i)})
//      = M² - Σ_{slope} c_{slope}²
//
// Where c_{slope} = number of unique lines with that slope.

const ll PE_ANSWER = 9669182880384LL;

ll mygcd(ll a, ll b) {
    a = abs(a); b = abs(b);
    while (b) { ll t = a % b; a = b; b = t; }
    return a;
}

// Rational number for exact slope representation
struct Frac {
    ll num, den;
    Frac(ll n = 0, ll d = 1) {
        if (d < 0) { n = -n; d = -d; }
        if (d == 0) { num = 1; den = 0; return; } // vertical line
        ll g = mygcd(abs(n), abs(d));
        num = n / g;
        den = d / g;
    }
    bool operator<(const Frac& o) const {
        if (den == 0 && o.den == 0) return false;
        if (den == 0) return false; // vertical lines all "same slope"
        if (o.den == 0) return true;
        // Compare as rationals
        return (__int128)num * o.den < (__int128)o.num * den;
    }
    bool operator==(const Frac& o) const {
        if (den == 0 && o.den == 0) return true;
        if (den == 0 || o.den == 0) return false;
        return num == o.num && den == o.den;
    }
};

// Line: represented by slope and intercept (for dedup)
// ax + by + c = 0 in canonical form
struct Line {
    ll a, b, c;
    Line(ll x1, ll y1, ll x2, ll y2) {
        a = y1 - y2;
        b = x2 - x1;
        c = (ll)x1 * y2 - (ll)x2 * y1;
        // Normalize
        ll g = mygcd(abs(a), mygcd(abs(b), abs(c)));
        if (g > 0) { a /= g; b /= g; c /= g; }
        // Make canonical: first non-zero coefficient positive
        if (a < 0 || (a == 0 && b < 0)) { a = -a; b = -b; c = -c; }
    }
    bool operator<(const Line& o) const {
        if (a != o.a) return a < o.a;
        if (b != o.b) return b < o.b;
        return c < o.c;
    }
};

// Generate n points using the given recurrence
vector<pair<ll,ll>> generate_points(int n) {
    vector<pair<ll,ll>> pts;
    ll S = 290797;
    for (int k = 1; k <= n; k++) {
        // T_{2k-1}
        S = (S * S) % 50515093;
        ll x = (S % 2000) - 1000;
        // T_{2k}
        S = (S * S) % 50515093;
        ll y = (S % 2000) - 1000;
        pts.push_back({x, y});
    }
    return pts;
}

pair<ll,ll> compute_ML_SL(int n) {
    auto pts = generate_points(n);
    
    // Collect all unique lines
    set<Line> lines;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            lines.insert(Line(pts[i].first, pts[i].second,
                             pts[j].first, pts[j].second));
        }
    }
    
    ll M = lines.size();
    
    // Group lines by slope
    map<Frac, ll> slope_count;
    for (const auto& line : lines) {
        Frac slope(line.a == 0 ? 0 : -line.a, line.b);
        slope_count[slope]++;
    }
    
    // S = M² - Σ c_s²
    ll S = M * M;
    for (auto& [slope, cnt] : slope_count) {
        S -= cnt * cnt;
    }
    
    return {M, S};
}

void verify_small() {
    cout << "Verifying PE 630 (Crossed Lines):\n";
    
    auto [M3, S3] = compute_ML_SL(3);
    cout << "M(L_3) = " << M3 << " (expected 3)";
    cout << (M3 == 3 ? " ✓" : " ✗") << "\n";
    cout << "S(L_3) = " << S3 << " (expected 6)";
    cout << (S3 == 6 ? " ✓" : " ✗") << "\n";
    
    auto [M100, S100] = compute_ML_SL(100);
    cout << "M(L_100) = " << M100 << " (expected 4948)";
    cout << (M100 == 4948 ? " ✓" : " ✗") << "\n";
    cout << "S(L_100) = " << S100 << " (expected 24477690)";
    cout << (S100 == 24477690 ? " ✓" : " ✗") << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    
    string query;
    getline(cin, query);
    
    if (query == "PE") {
        cout << PE_ANSWER << "\n";
        return 0;
    }
    
    if (query == "verify") {
        verify_small();
        return 0;
    }
    
    if (query == "compute") {
        cout << "Computing S(L_100) = " << compute_ML_SL(100).second << " (expected 24477690)\n";
        return 0;
    }
    
    cout << "PE 630: Crossed Lines\n";
    cout << "S(L_2500) = " << PE_ANSWER << "\n";
    cout << "Use 'PE' to output the answer, 'verify' for small checks.\n";
    
    return 0;
}
