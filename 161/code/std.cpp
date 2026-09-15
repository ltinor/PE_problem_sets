#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 161: 三联骨牌拼法计数
// 轮廓线DP: 逐格扫描，mask表示前方2W个格子的填充状态

int W, H;

// 检查在(r,c)处放置形状s是否合法，并返回新mask（已shifted）
// shapes: 六种三联骨牌，编码为(dr1,dc1, dr2,dc2)
const int shapes[6][4] = {
    {0,1, 0,2},     // 水平横条
    {1,0, 2,0},     // 竖直条
    {0,1, 1,0},     // L: ┌
    {0,1, 1,1},     // L: ┐
    {1,0, 1,1},     // L: └
    {1,0, 1,-1},    // L: ┘
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> W >> H;

    if((1LL * W * H) % 3 != 0){
        cout << "0\n";
        return 0;
    }

    int total = W * H;
    int MS = 2 * W + 2;  // mask需要覆盖到位置2W

    // dp[mask]：当前mask的方案数
    map<ll, ll> dp;
    dp[0] = 1;

    for(int pos = 0; pos < total; pos++){
        int r = pos / W;
        int c = pos % W;

        map<ll, ll> ndp;
        for(auto &[mask, cnt] : dp){
            if(mask & 1){
                // 当前格已填充，右移继续
                ll nmask = mask >> 1;
                ndp[nmask] += cnt;
            } else {
                // 尝试六种放置
                for(int s=0; s<6; s++){
                    int dr1 = shapes[s][0], dc1 = shapes[s][1];
                    int dr2 = shapes[s][2], dc2 = shapes[s][3];

                    int nr1 = r + dr1, nc1 = c + dc1;
                    int nr2 = r + dr2, nc2 = c + dc2;

                    // 边界检查
                    if(nr1 >= H || nc1 < 0 || nc1 >= W) continue;
                    if(nr2 >= H || nc2 < 0 || nc2 >= W) continue;

                    int b1 = dr1 * W + dc1;
                    int b2 = dr2 * W + dc2;

                    // 检查这些位置是否已被占用
                    if((mask >> b1) & 1) continue;
                    if((mask >> b2) & 1) continue;

                    ll nmask = mask | (1LL << b1) | (1LL << b2);
                    nmask >>= 1;
                    ndp[nmask] += cnt;
                }
            }
        }
        dp = std::move(ndp);
    }

    cout << dp[0] << "\n";
}
