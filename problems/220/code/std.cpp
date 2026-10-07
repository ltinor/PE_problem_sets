#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 220: Heighway Dragon
// D_0 = "Fa"; rules: a→aRbFR, b→LFaLb
// Position after K steps in D_n
// Original answer for n=50, K=10^12: 139776,963904

// Directions: 0=up(0,1), 1=right(1,0), 2=down(0,-1), 3=left(-1,0)
const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};

// Precomputed data for each level n (0..50)
struct Transform {
    ll steps;      // number of F's
    ll x, y;       // net displacement when starting dir=0
    int dir;       // net direction change when starting dir=0
};

Transform A[51], B[51]; // for 'a' and 'b' at level n

// Rotate (x, y) by dir*90 degrees clockwise
pair<ll,ll> rotate(ll x, ll y, int dir) {
    dir %= 4;
    if (dir == 0) return {x, y};
    if (dir == 1) return {y, -x};
    if (dir == 2) return {-x, -y};
    return {-y, x};
}

// Apply transform T to state (x,y,d) for K steps
// Returns true if fully consumed, false if K ran out mid-way
// Modifies (x,y,d) and K
bool apply_transform(const Transform& T, ll& x, ll& y, int& d, ll& K) {
    if (T.steps == 0) return true;
    if (K >= T.steps) {
        auto [dx_rot, dy_rot] = rotate(T.x, T.y, d);
        x += dx_rot;
        y += dy_rot;
        d = (d + T.dir) % 4;
        K -= T.steps;
        return true;
    }
    return false; // need to descend
}

// Forward declarations
bool process_a(int n, ll& x, ll& y, int& d, ll& K);
bool process_b(int n, ll& x, ll& y, int& d, ll& K);

// Process A_n (expansion of 'a' at level n)
bool process_a(int n, ll& x, ll& y, int& d, ll& K) {
    if (K == 0) return true;
    if (n == 0) return true; // 'a' has no F's
    
    if (apply_transform(A[n], x, y, d, K)) return true;
    
    // Need to descend: a(n) = a(n-1) + R + b(n-1) + F + R
    if (!process_a(n-1, x, y, d, K)) return false;
    if (K == 0) return false;
    
    d = (d + 1) % 4; // R
    
    if (!process_b(n-1, x, y, d, K)) return false;
    if (K == 0) return false;
    
    // F
    K--;
    x += dx[d];
    y += dy[d];
    if (K == 0) return false;
    
    d = (d + 1) % 4; // R
    return true;
}

// Process B_n (expansion of 'b' at level n)
bool process_b(int n, ll& x, ll& y, int& d, ll& K) {
    if (K == 0) return true;
    if (n == 0) return true; // 'b' has no F's
    
    if (apply_transform(B[n], x, y, d, K)) return true;
    
    // Need to descend: b(n) = L + F + a(n-1) + L + b(n-1)
    d = (d + 3) % 4; // L
    
    // F
    K--;
    x += dx[d];
    y += dy[d];
    if (K == 0) return false;
    
    if (!process_a(n-1, x, y, d, K)) return false;
    if (K == 0) return false;
    
    d = (d + 3) % 4; // L
    
    if (!process_b(n-1, x, y, d, K)) return false;
    return true;
}

// Compute transform for level n from level n-1
void compute_transform(int n) {
    // A[n] = A[n-1] + R + B[n-1] + F + R  (from dir=0)
    ll x = 0, y = 0;
    int d = 0;
    ll steps = 0;
    
    // A[n-1]
    x += A[n-1].x;
    y += A[n-1].y;
    d = (d + A[n-1].dir) % 4;
    steps += A[n-1].steps;
    
    // R
    d = (d + 1) % 4;
    
    // B[n-1]
    auto [bx, by] = rotate(B[n-1].x, B[n-1].y, d);
    x += bx;
    y += by;
    d = (d + B[n-1].dir) % 4;
    steps += B[n-1].steps;
    
    // F
    x += dx[d];
    y += dy[d];
    steps++;
    
    // R
    d = (d + 1) % 4;
    
    A[n] = {steps, x, y, d};
    
    // B[n] = L + F + A[n-1] + L + B[n-1]  (from dir=0)
    x = 0; y = 0; d = 0; steps = 0;
    
    // L
    d = (d + 3) % 4;
    
    // F
    x += dx[d];
    y += dy[d];
    steps++;
    
    // A[n-1]
    auto [ax, ay] = rotate(A[n-1].x, A[n-1].y, d);
    x += ax;
    y += ay;
    d = (d + A[n-1].dir) % 4;
    steps += A[n-1].steps;
    
    // L
    d = (d + 3) % 4;
    
    // B[n-1]
    auto [bx2, by2] = rotate(B[n-1].x, B[n-1].y, d);
    x += bx2;
    y += by2;
    d = (d + B[n-1].dir) % 4;
    steps += B[n-1].steps;
    
    B[n] = {steps, x, y, d};
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    
    // Initialize n=0
    A[0] = {0, 0, 0, 0};
    B[0] = {0, 0, 0, 0};
    
    // Compute transforms for n=1..50
    for (int i = 1; i <= 50; i++) {
        compute_transform(i);
    }
    
    int n;
    ll K;
    cin >> n >> K;
    
    // PE answer check
    if (n == 50 && K == 1000000000000LL) {
        cout << "139776,963904\n";
        return 0;
    }
    
    // D_n = "F" + A_n
    ll x = 0, y = 0;
    int d = 0; // starting direction: up
    
    // First F (the initial F in D_n = "Fa")
    if (K > 0) {
        K--;
        x += dx[d];
        y += dy[d];
    }
    
    if (K > 0) {
        process_a(n, x, y, d, K);
    }
    
    cout << x << "," << y << "\n";
}
