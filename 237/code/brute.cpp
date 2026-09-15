#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 237: Tours - brute force enumeration for small n
// Uses BFS/DFS to enumerate all Hamiltonian paths on 4×n board

int n;
int ans = 0;
bool vis[4][20];

const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};

void dfs(int x, int y, int steps, int total) {
    if (x == 3 && y == 0 && steps == total) {
        ans++;
        return;
    }
    for (int d = 0; d < 4; d++) {
        int nx = x + dx[d], ny = y + dy[d];
        if (nx >= 0 && nx < 4 && ny >= 0 && ny < n && !vis[nx][ny]) {
            vis[nx][ny] = true;
            dfs(nx, ny, steps + 1, total);
            vis[nx][ny] = false;
        }
    }
}

int main() {
    cin >> n;
    if (n > 5) { cout << "0\n"; return 0; } // too large for brute
    memset(vis, 0, sizeof(vis));
    vis[0][0] = true;
    ans = 0;
    dfs(0, 0, 1, 4 * n);
    cout << ans << "\n";
    return 0;
}
