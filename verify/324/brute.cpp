#include<bits/stdc++.h>
using namespace std;
#define ll long long

const ll MOD = 100000007;

// Brute force for small n: enumerate all tilings
// Uses DFS on the 3×3×n grid

int n;
int g[3][3][20]; // grid up to n=5 for brute force
int cnt;

// Block shapes: 
// Horizontal in xy-plane: 2×1×1 = dir (dx) or (dy)
// Vertical in z: 1×1×2 = dir (dz)
const int dx[4] = {0, 0, 1, -1};
const int dy[4] = {1, -1, 0, 0};
const int dz[4] = {0, 0, 0, 0};

void dfs(int x, int y, int z) {
    if (z >= n) { cnt++; return; }
    if (y >= 3) { dfs(0, y+1, z); return; }
    if (x >= 3) { dfs(0, y, z+1); return; }
    if (g[x][y][z] != 0) {
        dfs(x+1, y, z);
        return;
    }

    // Try placing a block starting at (x,y,z)
    // 1. Horizontal in x direction (2,1,1) -> covers (x,y,z) and (x+1,y,z)
    if (x+1 < 3 && g[x+1][y][z] == 0) {
        g[x][y][z] = g[x+1][y][z] = 1;
        dfs(x+2, y, z);
        g[x][y][z] = g[x+1][y][z] = 0;
    }
    // 2. Horizontal in y direction (1,2,1) -> covers (x,y,z) and (x,y+1,z)
    if (y+1 < 3 && g[x][y+1][z] == 0) {
        g[x][y][z] = g[x][y+1][z] = 1;
        dfs(x+1, y, z);
        g[x][y][z] = g[x][y+1][z] = 0;
    }
    // 3. Vertical in z direction (1,1,2) -> covers (x,y,z) and (x,y,z+1)
    if (z+1 < n && g[x][y][z+1] == 0) {
        g[x][y][z] = g[x][y][z+1] = 1;
        dfs(x+1, y, z);
        g[x][y][z] = g[x][y][z+1] = 0;
    }
}

ll brute_f(int n_val) {
    n = n_val;
    cnt = 0;
    memset(g, 0, sizeof(g));
    dfs(0, 0, 0);
    return cnt % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n_val = stoi(s);

    if (n_val > 4) {
        // Too slow for brute force, return -1 for checking
        cout << "-1\n";
        return 0;
    }

    cout << brute_f(n_val) << "\n";
    return 0;
}
