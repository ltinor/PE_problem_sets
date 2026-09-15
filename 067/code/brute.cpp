#include<bits/stdc++.h>
using namespace std;

int R;
vector<vector<int>> a;
int ans;

void dfs(int i, int j, int sum){
    if(i == R){
        ans = max(ans, sum);
        return;
    }
    dfs(i+1, j, sum + a[i][j]);
    dfs(i+1, j+1, sum + a[i][j]);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> R;
    a.assign(R, vector<int>(R));
    for(int i = 0; i < R; i++){
        for(int j = 0; j <= i; j++){
            cin >> a[i][j];
        }
    }

    ans = 0;
    dfs(0, 0, 0);
    cout << ans << "\n";
    return 0;
}
