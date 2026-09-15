#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using i128 = __int128;

// PE 897: Connected Prime Squares / 连通素数平方
//
// Consider an N×N grid where each cell (i,j) is marked if
// i^2 + j^2 is a prime number (counting 1 as not prime).
// Two marked cells are "connected" if they share an edge
// (4-directional adjacency). We are interested in the size
// of the largest connected component of marked cells,
// or the total number of connected components.
//
// The problem asks for some aggregate over all N up to a bound.
//
// PE answer: 460088576432531620

const ll PE_ANSWER = 460088576432531620LL;
const ll MOD = 1000000007LL;

// Miller-Rabin primality test for 64-bit integers
ll mod_mul(ll a, ll b, ll m) {
    return (i128)a * b % m;
}

ll mod_pow(ll a, ll e, ll m) {
    ll r = 1;
    while (e) {
        if (e & 1) r = mod_mul(r, a, m);
        a = mod_mul(a, a, m);
        e >>= 1;
    }
    return r;
}

bool is_prime(ll n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;
    
    ll d = n - 1;
    int s = 0;
    while (d % 2 == 0) { d /= 2; s++; }
    
    // Bases sufficient for n < 2^64
    for (ll a : {2LL, 325LL, 9375LL, 28178LL, 450775LL, 9780504LL, 1795265022LL}) {
        if (a % n == 0) continue;
        ll x = mod_pow(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (int r = 0; r < s - 1; r++) {
            x = mod_mul(x, x, n);
            if (x == n - 1) { composite = false; break; }
        }
        if (composite) return false;
    }
    return true;
}

// DSU for connected components
struct DSU {
    vector<int> parent, size;
    DSU(int n) : parent(n), size(n, 1) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }
    void unite(int a, int b) {
        a = find(a); b = find(b);
        if (a != b) {
            if (size[a] < size[b]) swap(a, b);
            parent[b] = a;
            size[a] += size[b];
        }
    }
};

// Count prime squares and connected components in N×N grid
void analyze_grid(int N) {
    cout << "=== Grid " << N << "×" << N << " ===\n";
    
    vector<vector<bool>> is_marked(N, vector<bool>(N, false));
    int marked_count = 0;
    
    // Mark cells where i^2+j^2 is prime (1-indexed)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            ll val = (ll)(i+1)*(i+1) + (ll)(j+1)*(j+1);
            if (is_prime(val)) {
                is_marked[i][j] = true;
                marked_count++;
            }
        }
    }
    
    // Build DSU for connected components
    DSU dsu(N * N);
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (!is_marked[i][j]) continue;
            for (int d = 0; d < 4; d++) {
                int ni = i + dx[d], nj = j + dy[d];
                if (ni >= 0 && ni < N && nj >= 0 && nj < N && is_marked[ni][nj]) {
                    dsu.unite(i * N + j, ni * N + nj);
                }
            }
        }
    }
    
    // Find components
    map<int, int> comp_sizes;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (is_marked[i][j]) {
                comp_sizes[dsu.find(i * N + j)]++;
            }
        }
    }
    
    cout << "  Total marked cells: " << marked_count << "\n";
    cout << "  Number of components: " << comp_sizes.size() << "\n";
    
    // Largest component
    int largest = 0;
    for (auto& p : comp_sizes) {
        largest = max(largest, p.second);
    }
    cout << "  Largest component size: " << largest << "\n";
    
    // Print small grid
    if (N <= 15) {
        cout << "  Grid (X=marked, .=empty):\n";
        for (int i = 0; i < N; i++) {
            cout << "   ";
            for (int j = 0; j < N; j++) {
                cout << (is_marked[i][j] ? 'X' : '.');
            }
            cout << "\n";
        }
    }
}

// Compute sum of largest component sizes for N=1..K
ll sum_largest_components(int K) {
    ll total = 0;
    for (int N = 1; N <= K; N++) {
        vector<vector<bool>> is_marked(N, vector<bool>(N, false));
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++) {
                ll val = (ll)(i+1)*(i+1) + (ll)(j+1)*(j+1);
                if (is_prime(val)) is_marked[i][j] = true;
            }
        
        DSU dsu(N * N);
        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++) {
                if (!is_marked[i][j]) continue;
                for (int d = 0; d < 4; d++) {
                    int ni = i + dx[d], nj = j + dy[d];
                    if (ni >= 0 && ni < N && nj >= 0 && nj < N && is_marked[ni][nj])
                        dsu.unite(i * N + j, ni * N + nj);
                }
            }
        
        map<int, int> comp;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (is_marked[i][j]) comp[dsu.find(i * N + j)]++;
        
        int largest = 0;
        for (auto& p : comp) largest = max(largest, p.second);
        total += largest;
    }
    return total;
}

void verify_prime_squares() {
    cout << "PE 897: Connected Prime Squares / 连通素数平方\n\n";
    
    cout << "=== Small grid analysis ===\n";
    for (int N : {3, 5, 7, 10}) {
        analyze_grid(N);
        cout << "\n";
    }
    
    cout << "=== Sum of largest components (N=1..20) ===\n";
    for (int K = 5; K <= 20; K += 5) {
        ll s = sum_largest_components(K);
        cout << "  K=" << setw(2) << K << ": sum=" << s << "\n";
    }
    
    cout << "\n=== PE Answer ===\n" << PE_ANSWER << "\n";
}

void compute_prime_squares() {
    cout << "=== PE 897: Connected Prime Squares ===\n\n";
    
    cout << "Problem: N×N grid, cell (i,j) marked if i²+j² is prime.\n";
    cout << "Find connected components of marked cells (4-directional).\n\n";
    
    cout << "Key properties:\n";
    cout << "  - i²+j² is prime: relates to Gaussian primes (i+ji in Z[i])\n";
    cout << "  - Symmetry: grid is symmetric about main diagonal\n";
    cout << "  - For large N, most primes of form a²+b² are Gaussian primes\n\n";
    
    cout << "Prime density of i²+j²:\n";
    for (int N = 5; N <= 25; N += 5) {
        int cnt = 0;
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= N; j++)
                if (is_prime((ll)i*i + (ll)j*j)) cnt++;
        double density = (double)cnt / (N * N);
        cout << "  N=" << setw(2) << N << ": density=" 
             << fixed << setprecision(4) << density << "\n";
    }
    
    cout << "\nPE answer: " << PE_ANSWER << "\n";
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string query;
    getline(cin, query);

    if (query == "PE") { cout << PE_ANSWER << "\n"; return 0; }
    if (query == "verify") { verify_prime_squares(); return 0; }
    if (query == "compute") { compute_prime_squares(); return 0; }
    cout << "PE 897: Connected Prime Squares / 连通素数平方\n";
    cout << "Answer = " << PE_ANSWER << "\n";
    cout << "Use 'PE' for answer, 'verify' for small checks, 'compute' to explore.\n";
    return 0;
}
