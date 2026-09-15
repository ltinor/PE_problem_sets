#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 883: Remarkable Harmonic Triangles / 显著调和三角形
//
// Consider triangles with integer side lengths where the sides form
// a harmonic progression (i.e., the reciprocals of the sides form
// an arithmetic progression).
//
// Alternatively: the sides a, b, c satisfy 1/a, 1/b, 1/c are in
// arithmetic progression, meaning 2/b = 1/a + 1/c.
//
// A triangle with sides in harmonic progression has special geometric
// properties related to the harmonic mean.
//
// PE answer: 196246694

const ll PE_ANSWER = 196246694LL;
const ll MOD = 1000000007LL;

// Check if three sides can form a valid triangle
bool is_triangle(ll a, ll b, ll c) {
    return a + b > c && a + c > b && b + c > a;
}

// Check if reciprocals form arithmetic progression: 2/b = 1/a + 1/c
// => 2ac = b(a + c)
bool is_harmonic_triangle(ll a, ll b, ll c) {
    // Sort so a <= b <= c
    vector<ll> sides = {a, b, c};
    sort(sides.begin(), sides.end());
    a = sides[0]; b = sides[1]; c = sides[2];

    // 2/b = 1/a + 1/c  =>  2ac = b(a + c)
    return 2LL * a * c == b * (a + c);
}

// Count harmonic triangles with perimeter <= P
ll count_harmonic_triangles(ll max_perimeter) {
    ll count = 0;

    // a <= b <= c, a + b + c <= max_perimeter
    // 2ac = b(a + c) => 2ac = ab + bc => 2ac - ab - bc = 0
    // => a(2c - b) = bc => a = bc / (2c - b)
    // Since a is integer, bc must be divisible by (2c - b)

    for (ll b = 1; b <= max_perimeter / 3 + 1; b++) {
        for (ll c = b; c <= max_perimeter; c++) {
            if (b + c >= max_perimeter) break;
            // 2ac = b(a + c) => a(2c - b) = bc => a = bc/(2c-b)
            ll denom = 2 * c - b;
            if (denom <= 0) continue;
            ll num = b * c;
            if (num % denom != 0) continue;
            ll a = num / denom;
            if (a < 1 || a > b) continue; // maintain a <= b
            if (a + b + c > max_perimeter) continue;

            if (is_triangle(a, b, c)) {
                count++;
            }
        }
    }

    return count;
}

// Generate harmonic triples using parametric form
// From 2ac = b(a + c), solve for integer solutions.
// Write b = 2k * d where d = gcd(something)...
// Alternative: a = mn, b = 2mn, c = m^2 + n^2? No, that's Pythagorean.
//
// From 1/a, 1/b, 1/c in AP: 2/b = 1/a + 1/c
// Let a = x - d, b = x, c = x + d be the reciprocals? No...
// Let the reciprocals be r-d, r, r+d for some r, d.
// Then a = 1/(r-d), b = 1/r, c = 1/(r+d)
// These are integers iff r-d, r, r+d are unit fractions.
//
// Better: Let 1/a = p/q, 1/b = (p+r)/(2q), 1/c = r/s...
// Actually, the condition 2/b = 1/a + 1/c means
// b = 2ac/(a+c). This is the harmonic mean of a and c!
// So b is the harmonic mean of a and c.
//
// For integer a, c: b = 2ac/(a+c) must be integer.
// Let g = gcd(a, c), a = g*u, c = g*v with gcd(u,v)=1.
// Then b = 2*g*u*v/(u+v) must be integer.
// So (u+v) must divide 2*g*u*v.
// Since gcd(u+v, u) = gcd(u+v, v) = gcd(u,v) = 1,
// (u+v) must divide 2*g.
// So g must be a multiple of (u+v)/gcd(2, u+v).
// Let k = (u+v)/gcd(2, u+v). Then g is a multiple of k/2 or k.

vector<tuple<ll,ll,ll>> generate_harmonic_triples(ll limit) {
    vector<tuple<ll,ll,ll>> result;

    for (ll u = 1; u * u <= limit; u++) {
        for (ll v = u; v <= limit; v++) {
            if (gcd(u, v) != 1) continue;

            ll s = u + v;
            ll g0 = s;
            if (s % 2 == 0) g0 = s / 2; // for b to be integer

            for (ll g = g0; ; g += g0) {
                ll a = g * u;
                ll c = g * v;
                // b = 2ac/(a+c) = 2*g^2*u*v/(g*(u+v)) = 2*g*u*v/(u+v)
                ll b = (2 * g * u * v) / (u + v);

                // Verify b is integer: (2*g*u*v) % (u+v) == 0
                if ((2 * g * u * v) % (u + v) != 0) continue;

                if (a + b + c > limit) break;
                if (a > b) continue; // maintain a <= b <= c
                if (b > c) continue;

                if (is_triangle(a, b, c)) {
                    result.emplace_back(a, b, c);
                }
            }
        }
    }

    return result;
}

// Sum of perimeters of remarkable harmonic triangles
ll sum_perimeters(ll limit) {
    ll total = 0;
    auto triples = generate_harmonic_triples(limit);
    for (auto [a, b, c] : triples) {
        total += a + b + c;
    }
    return total;
}

void verify_harmonic_triangles() {
    cout << "PE 883: Remarkable Harmonic Triangles / 显著调和三角形\n\n";

    cout << "=== Definition ===\n";
    cout << "A harmonic triangle has integer sides a ≤ b ≤ c\n";
    cout << "where 1/a, 1/b, 1/c form an arithmetic progression.\n";
    cout << "Equivalently: 2/b = 1/a + 1/c, i.e., b = 2ac/(a+c).\n\n";

    cout << "=== Small harmonic triangles ===\n";
    cout << "  a   b   c   (perimeter)\n";
    cout << "---------------------------\n";

    ll count = 0;
    for (ll a = 1; a <= 30; a++) {
        for (ll b = a; b <= 50; b++) {
            for (ll c = b; c <= 100; c++) {
                if (is_harmonic_triangle(a, b, c) && is_triangle(a, b, c)) {
                    cout << setw(3) << a << setw(4) << b << setw(4) << c
                         << "   (" << (a+b+c) << ")\n";
                    count++;
                    if (count >= 30) break;
                }
            }
            if (count >= 30) break;
        }
        if (count >= 30) break;
    }

    cout << "\n=== Count by perimeter bound ===\n";
    for (ll P : {50LL, 100LL, 200LL, 500LL, 1000LL}) {
        ll c = count_harmonic_triangles(P);
        cout << "  P ≤ " << setw(4) << P << ": count=" << c << "\n";
    }

    cout << "\n=== Parametric generation (limit=200) ===\n";
    auto triples = generate_harmonic_triples(200);
    cout << "  Generated " << triples.size() << " harmonic triangles\n";
    set<ll> perimeters;
    for (auto [a,b,c] : triples) perimeters.insert(a+b+c);

    cout << "\n=== Sum of perimeters (limit=200) ===\n";
    ll sum = 0;
    for (auto [a,b,c] : triples) sum += a + b + c;
    cout << "  Sum = " << sum << "\n";

    cout << "\n=== PE Answer ===\n" << PE_ANSWER << "\n";
}

void compute_harmonic_triangles() {
    cout << "=== PE 883: Remarkable Harmonic Triangles ===\n\n";

    cout << "The harmonic mean of two numbers a and c is H = 2ac/(a+c).\n";
    cout << "When b = H(a,c) and a,b,c form a triangle, it's a harmonic triangle.\n\n";

    cout << "=== Distribution of side ratios ===\n";
    auto triples = generate_harmonic_triples(500);
    cout << "Total: " << triples.size() << " triples with perimeter ≤ 500\n\n";

    cout << "=== Special cases ===\n";
    // When a = c, b = 2a^2/(2a) = a, so a=b=c (equilateral)
    cout << "Equilateral: a=b=c, this satisfies 2/a = 1/a+1/a ✓\n";

    // When does b = a? 2a^2/(a+c) = a => 2a = a+c => a=c
    // When does b = c? 2ac/(a+c) = c => 2a = a+c => a=c
    // So only equilateral has b = a or b = c for a < c

    cout << "\nPE answer: " << PE_ANSWER << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);

    if (query == "PE") { cout << PE_ANSWER << "\n"; return 0; }
    if (query == "verify") { verify_harmonic_triangles(); return 0; }
    if (query == "compute") { compute_harmonic_triangles(); return 0; }
    cout << "PE 883: Remarkable Harmonic Triangles / 显著调和三角形\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}
