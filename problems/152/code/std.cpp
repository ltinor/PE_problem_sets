#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 i128;

i128 mygcd(i128 a, i128 b) { while(b){ i128 t=b; b=a%b; a=t; } return a; }

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int N; cin >> N;
    
    // Compute LCM using __int128
    i128 LCM = 1;
    for(int i=2; i<=N; i++) {
        i128 sq = (i128)i * i;
        i128 g = mygcd(LCM, sq);
        LCM = LCM / g * sq;
    }
    
    i128 target = LCM / 2;
    
    int half = N/2;
    // Left: indices 2..half
    vector<pair<i128, int>> left;
    int left_cnt = half - 1; // positions 2..half
    for(int mask=0; mask<(1<<left_cnt); mask++) {
        i128 sum = 0;
        for(int j=0; j<left_cnt; j++)
            if(mask & (1<<j))
                sum += LCM / ((i128)(2+j)*(2+j));
        left.push_back({sum, 0});
    }
    sort(left.begin(), left.end(), [](auto& a, auto& b){ return a.first < b.first; });
    
    // Right: indices half+1..N
    int right_cnt = N - half;
    ll ans = 0;
    for(int mask=0; mask<(1<<right_cnt); mask++) {
        i128 sum = 0;
        for(int j=0; j<right_cnt; j++)
            if(mask & (1<<j))
                sum += LCM / ((i128)(half+1+j)*(half+1+j));
        i128 need = target - sum;
        auto lo = lower_bound(left.begin(), left.end(), make_pair(need, 0),
            [](auto& a, auto& b){ return a.first < b.first; });
        auto hi = upper_bound(left.begin(), left.end(), make_pair(need, 0),
            [](auto& a, auto& b){ return a.first < b.first; });
        ans += hi - lo;
    }
    
    cout << ans << "\n";
}
