#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE331: Cross Flips
// Move at (i,j) flips all cells (r,c) where r==i OR c==j
// Solve A*X = CN over GF(2) with minimum Hamming weight
// For even N: A has full rank, unique solution
// For odd N: A has nullspace of dimension 2(N-1), enumerate for min weight

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin >> N;
    
    int n2 = N*N;
    
    // Build CN configuration
    ll lo = (ll)(N-1)*(N-1), hi = (ll)N*N;
    vector<int> CN(n2, 0);
    for (int x = 0; x < N; x++)
        for (int y = 0; y < N; y++) {
            ll d2 = (ll)x*x + (ll)y*y;
            if (d2 >= lo && d2 < hi) CN[x*N + y] = 1;
        }
    
    // Build move effect matrix A (n2 × n2)
    // A[mi][rc] = 1 if move at mi=(i,j) affects cell rc=(r,c)
    // affected if r==i OR c==j
    vector<vector<int>> A(n2, vector<int>(n2, 0));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            int mi = i*N + j;
            for (int r = 0; r < N; r++)
                for (int c = 0; c < N; c++)
                    A[mi][r*N + c] = (r == i || c == j) ? 1 : 0;
        }
    
    // Augmented matrix for Gaussian elimination
    vector<vector<int>> aug = A;
    for (int r = 0; r < n2; r++) aug[r].push_back(CN[r]);
    
    int rank = 0;
    vector<int> pivot_col(n2, -1);
    
    for (int col = 0; col < n2; col++) {
        int row = -1;
        for (int r = rank; r < n2; r++)
            if (aug[r][col] == 1) { row = r; break; }
        if (row == -1) continue;
        swap(aug[rank], aug[row]);
        pivot_col[rank] = col;
        for (int r = 0; r < n2; r++)
            if (r != rank && aug[r][col] == 1)
                for (int c = 0; c <= n2; c++)
                    aug[r][c] ^= aug[rank][c];
        rank++;
    }
    
    // Check consistency
    for (int r = rank; r < n2; r++)
        if (aug[r][n2] == 1) {
            cout << "0\n";
            return 0;
        }
    
    // Particular solution (free vars = 0)
    vector<int> base_X(n2, 0);
    for (int r = 0; r < rank; r++)
        base_X[pivot_col[r]] = aug[r][n2];
    
    // Find free columns and nullspace basis
    vector<bool> is_pivot(n2, false);
    for (int r = 0; r < rank; r++) is_pivot[pivot_col[r]] = true;
    
    vector<vector<int>> nullspace;
    for (int free_col = 0; free_col < n2; free_col++) {
        if (is_pivot[free_col]) continue;
        vector<int> ns_vec(n2, 0);
        ns_vec[free_col] = 1;
        for (int r = 0; r < rank; r++)
            ns_vec[pivot_col[r]] = aug[r][free_col];
        nullspace.push_back(ns_vec);
    }
    
    int ns_dim = (int)nullspace.size();
    
    // Enumerate nullspace to find minimum weight solution
    int min_wt = n2 + 1;
    int total = 1 << ns_dim;
    
    for (int mask = 0; mask < total; mask++) {
        vector<int> X = base_X;
        for (int b = 0; b < ns_dim; b++) {
            if (mask & (1 << b)) {
                for (int p = 0; p < n2; p++)
                    X[p] ^= nullspace[b][p];
            }
        }
        int wt = 0;
        for (int v : X) wt += v;
        if (wt < min_wt) min_wt = wt;
    }
    
    cout << min_wt << "\n";
    return 0;
}
