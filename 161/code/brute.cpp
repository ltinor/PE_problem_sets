#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 161 brute: 对小网格用DFS回溯

int W, H;
vector<vector<bool>> used;
ll ans = 0;

// 六种骨牌形状 (dr1,dc1, dr2,dc2)
const int shapes[6][4] = {
    {0,1, 0,2},
    {1,0, 2,0},
    {0,1, 1,0},
    {0,1, 1,1},
    {1,0, 1,1},
    {1,0, 1,-1},
};

void dfs(int r, int c){
    // 找下一个空格
    while(r < H && used[r][c]){
        c++;
        if(c == W){ r++; c = 0; }
    }
    if(r == H){
        ans++;
        return;
    }

    for(int s=0; s<6; s++){
        int dr1 = shapes[s][0], dc1 = shapes[s][1];
        int dr2 = shapes[s][2], dc2 = shapes[s][3];

        int nr1 = r + dr1, nc1 = c + dc1;
        int nr2 = r + dr2, nc2 = c + dc2;

        if(nr1 >= H || nc1 < 0 || nc1 >= W) continue;
        if(nr2 >= H || nc2 < 0 || nc2 >= W) continue;
        if(used[nr1][nc1] || used[nr2][nc2]) continue;

        used[r][c] = used[nr1][nc1] = used[nr2][nc2] = true;
        dfs(r, c);
        used[r][c] = used[nr1][nc1] = used[nr2][nc2] = false;
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> W >> H;

    if((1LL * W * H) % 3 != 0){
        cout << "0\n";
        return 0;
    }

    if(W * H > 24){
        // 网格太大，用简单DP
        // 回退到std算法（同算法）
        int total = W * H;
        map<ll, ll> dp;
        dp[0] = 1;
        for(int pos = 0; pos < total; pos++){
            int r = pos / W, c = pos % W;
            map<ll, ll> ndp;
            for(auto &[mask, cnt] : dp){
                if(mask & 1){
                    ndp[mask>>1] += cnt;
                } else {
                    for(int s=0; s<6; s++){
                        int dr1=shapes[s][0], dc1=shapes[s][1];
                        int dr2=shapes[s][2], dc2=shapes[s][3];
                        int nr1=r+dr1, nc1=c+dc1;
                        int nr2=r+dr2, nc2=c+dc2;
                        if(nr1>=H||nc1<0||nc1>=W) continue;
                        if(nr2>=H||nc2<0||nc2>=W) continue;
                        int b1=dr1*W+dc1, b2=dr2*W+dc2;
                        if((mask>>b1)&1) continue;
                        if((mask>>b2)&1) continue;
                        ll nmask = mask | (1LL<<b1) | (1LL<<b2);
                        ndp[nmask>>1] += cnt;
                    }
                }
            }
            dp = std::move(ndp);
        }
        cout << dp[0] << "\n";
        return 0;
    }

    // 小网格暴力
    used.assign(H, vector<bool>(W, false));
    ans = 0;
    dfs(0, 0);
    cout << ans << "\n";
}
