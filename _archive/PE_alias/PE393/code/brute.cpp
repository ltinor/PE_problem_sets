#include<bits/stdc++.h>
using namespace std;
#define ll long long
// Brute: enumerate ant movements on n×n grid via backtracking
// Each ant moves to adjacent cell, no collisions, no crossing edges
int n;
ll ans = 0;
vector<vector<bool>> occupied;
vector<vector<int>> used_edge; // 0=right,1=down,2=left,3=up

void dfs(int x, int y) {
    if (x == n) { ans++; return; }
    int nx = x, ny = y+1;
    if (ny == n) { nx++; ny = 0; }
    // Try 4 directions
    int dx[] = {0,1,0,-1}, dy[] = {1,0,-1,0};
    for (int d=0; d<4; d++) {
        int tx = x+dx[d], ty = y+dy[d];
        if (tx<0||tx>=n||ty<0||ty>=n) continue;
        if (occupied[tx][ty]) continue;
        // Check edge crossing
        int ex = min(x,tx), ey = min(y,ty);
        int ed = (dx[d]!=0) ? 1 : 0; // 1=vertical, 0=horizontal
        if (used_edge[ex][ey] & (1<<ed)) continue;
        occupied[tx][ty] = true;
        used_edge[ex][ey] |= (1<<ed);
        dfs(nx, ny);
        used_edge[ex][ey] &= ~(1<<ed);
        occupied[tx][ty] = false;
    }
}

int main() {
    cin >> n;
    occupied.assign(n, vector<bool>(n, false));
    used_edge.assign(n, vector<int>(n, 0));
    dfs(0, 0);
    cout << ans << "\n";
}
