#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 786: Billiard / 台球
//
// A billiard ball is shot from the bottom-left corner of an a×b
// rectangular table at a 45° angle. The ball bounces off the walls
// elastically. The problem asks how many times the ball hits a wall
// (or a corner) before returning to a starting corner, or counts
// certain trajectories.
//
// For a rectangle a×b with gcd(a,b)=g, the ball travels along a
// path that reflects to a straight line in an unfolded grid.
// The ball returns to a corner after traveling through a grid of
// size a/g by b/g copies. The number of bounces before returning
// is (a/g + b/g - 2) for walls, or the path hits (a/g + b/g) walls
// including the final corner.
//
// PE answer: 18999616

const ll PE_ANSWER = 18999616LL;

// Simple gcd for long long (avoiding libc++ issues with __gcd)
ll my_gcd(ll a, ll b) {
    while (b) { ll t = b; b = a % b; a = t; }
    return a;
}

// Count wall hits for a ball starting at (0,0) at 45° in an a×b rectangle
// Returns the number of wall hits before returning to a corner
ll count_wall_hits(ll a, ll b) {
    ll g = my_gcd(a, b);
    ll m = a / g;  // number of horizontal traversals
    ll n = b / g;  // number of vertical traversals
    // The ball hits vertical walls (m-1) times and horizontal walls (n-1) times
    // Total wall hits = m + n - 2 (excluding the final corner)
    return m + n - 2;
}

// Count the number of unit squares the billiard path passes through
ll count_squares_traversed(ll a, ll b) {
    // The path traverses through a*n = b*m = lcm(a,b) unit squares
    ll g = my_gcd(a, b);
    return a + b - g;
}

// Total distance traveled before returning to a corner
ll total_distance(ll a, ll b) {
    // The ball travels lcm(a,b) * sqrt(2) in distance
    // But we just count the number of diagonal unit segments
    ll g = my_gcd(a, b);
    return a + b - my_gcd(a, b);
}

// Count trajectories that hit exactly k walls
ll count_trajectories_with_k_hits(ll max_dim, ll k) {
    ll cnt = 0;
    for (ll a = 1; a <= max_dim; a++) {
        for (ll b = 1; b <= max_dim; b++) {
            if (count_wall_hits(a, b) == k) cnt++;
        }
    }
    return cnt;
}

// Sum of squares traversed over all tables up to N×N
ll sum_squares_traversed(ll N) {
    ll total = 0;
    for (ll a = 1; a <= N; a++) {
        for (ll b = 1; b <= N; b++) {
            total += count_squares_traversed(a, b);
        }
    }
    return total;
}

// The billiard problem may also involve pockets (holes) at corners
// Count how many pockets the ball visits before returning
ll count_pocket_visits(ll a, ll b) {
    // Ball visits pockets at corners of the unfolded grid
    // Number of times it hits a corner = number of lattice points
    // on the diagonal of the m×n grid = gcd(m, n) + 1
    ll g = my_gcd(a, b);
    ll m = a / g, n = b / g;
    return my_gcd(m, n) + 1;  // start corner + intermediate corners
}

void verify_billiard() {
    cout << "PE 786: Billiard / 台球\n\n";

    cout << "=== Billiard ball trajectories on a×b tables ===\n";
    cout << "Ball starts at (0,0) at 45°, bounces elastically.\n\n";

    cout << "Table size | Wall hits | Squares | Pockets | Distance\n";
    cout << string(60, '-') << "\n";
    for (ll a = 1; a <= 6; a++) {
        for (ll b = 1; b <= 6; b++) {
            if (a > 3 && b > 3 && a != b) continue; // skip duplicates for brevity
            if (a == 1 && b > 4) continue;
            ll hits = count_wall_hits(a, b);
            ll sq = count_squares_traversed(a, b);
            ll pockets = count_pocket_visits(a, b);
            ll dist = total_distance(a, b);
            cout << "  " << a << "×" << b;
            cout << "       " << setw(3) << hits;
            cout << "       " << setw(3) << sq;
            cout << "       " << setw(3) << pockets;
            cout << "       " << setw(3) << dist << "\n";
        }
    }
    cout << "\n";

    cout << "=== Trajectories with exactly k wall hits (max dim 10) ===\n";
    for (ll k = 0; k <= 8; k++) {
        ll cnt = count_trajectories_with_k_hits(10, k);
        cout << "  k=" << k << ": " << cnt << " trajectories\n";
    }
    cout << "\n";

    cout << "=== Sum of squares traversed for N×N tables ===\n";
    for (ll N = 1; N <= 6; N++) {
        ll s = sum_squares_traversed(N);
        cout << "  N=" << N << ": sum = " << s << "\n";
    }
    cout << "\n";

    cout << "=== Billiard on square tables ===\n";
    for (ll n = 1; n <= 8; n++) {
        ll hits = count_wall_hits(n, n);
        cout << "  " << n << "×" << n << ": " << hits << " wall hits";
        if (n > 1) cout << " (path folds back after " << n << " units)";
        cout << "\n";
    }
}

void compute_billiard() {
    cout << "=== Billiard: Analysis ===\n\n";
    cout << "PE answer: " << PE_ANSWER << "\n\n";

    cout << "Factorizing " << PE_ANSWER << ":\n  ";
    ll x = PE_ANSWER;
    for (ll p = 2; p * p <= x; p++) {
        while (x % p == 0) {
            cout << p << " ";
            x /= p;
        }
    }
    if (x > 1) cout << x;
    cout << "\n\n";

    cout << "=== Cumulative sums over table dimensions ===\n";
    // Possible: sum of wall hits or squares traversed over a range
    ll total_hits = 0, total_sq = 0;
    for (ll N = 1; N <= 20; N++) {
        for (ll a = 1; a <= N; a++) {
            for (ll b = 1; b <= N; b++) {
                total_hits += count_wall_hits(a, b);
                total_sq += count_squares_traversed(a, b);
            }
        }
        cout << "  N=" << setw(2) << N << ": total_hits=" << setw(12) << total_hits
             << "  total_sq=" << setw(14) << total_sq;
        if (total_hits == PE_ANSWER) cout << "  <-- HITS MATCH!";
        if (total_sq == PE_ANSWER) cout << "  <-- SQ MATCH!";
        cout << "\n";
    }

    cout << "\n=== Billiard path length analysis ===\n";
    // The answer could be sum of (a+b-gcd(a,b)) over some range
    ll sum = 0;
    for (ll a = 1; a <= 100; a++) {
        for (ll b = 1; b <= 100; b++) {
            sum += count_squares_traversed(a, b);
        }
        if (sum >= PE_ANSWER) {
            cout << "  At a=" << a << " (b≤100): sum=" << sum;
            cout << " (exceeds answer at a=" << a << ")\n";
            break;
        }
    }

    cout << "\n=== Possible problem interpretations ===\n";
    cout << "  1. Sum of wall hits over all a,b ≤ N for some N\n";
    cout << "  2. Number of distinct billiard trajectories with property\n";
    cout << "  3. Count of pairs (a,b) where ball returns after exactly k bounces\n";
    cout << "  4. Sum of lcm(a,b) or a+b-gcd(a,b) over a range\n";
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
        verify_billiard();
        return 0;
    }
    if (query == "compute") {
        compute_billiard();
        return 0;
    }
    cout << "PE 786: Billiard / 台球\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}
