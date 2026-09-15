#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

// 189: Tri-colouring N rows of triangles (N ≤ 4, total ≤ 16 triangles)
// Row i has 2i+1 upward triangles and 2i downward triangles (alternating)

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int R; cin >> R; // rows of upward-pointing big triangles
    
    // Map triangle grid structure
    // upward triangles: (r,c) for r=0..R-1, c=0..r
    // downward triangles: (r,c) for r=0..R-2, c=0..r
    // Total: up=R(R+1)/2, down=R(R-1)/2, total=R^2
    
    int total = R*R;
    vector<vector<int>> adj(total);
    int idx=0;
    // Map position to index
    int up[5][5], down[5][5];
    memset(up,-1,sizeof(up)); memset(down,-1,sizeof(down));
    
    for(int r=0;r<R;r++)
        for(int c=0;c<=r;c++)
            up[r][c]=idx++;
    for(int r=0;r<R-1;r++)
        for(int c=0;c<=r;c++)
            down[r][c]=idx++;
    
    // Build adjacency
    for(int r=0;r<R;r++){
        for(int c=0;c<=r;c++){
            int u=up[r][c];
            // Up triangle neighbors: down(r-1,c-1), down(r-1,c), down(r,c-1), down(r,c)
            if(r>0&&c>0&&down[r-1][c-1]!=-1) adj[u].push_back(down[r-1][c-1]);
            if(r>0&&c<=r-1&&down[r-1][c]!=-1) adj[u].push_back(down[r-1][c]);
            if(c>0&&down[r][c-1]!=-1) adj[u].push_back(down[r][c-1]);
            if(c<=r-1&&down[r][c]!=-1) adj[u].push_back(down[r][c]);
        }
    }
    for(int r=0;r<R-1;r++){
        for(int c=0;c<=r;c++){
            int d=down[r][c];
            // Down triangle neighbors: up(r,c), up(r,c+1), up(r+1,c), up(r+1,c+1)
            adj[d].push_back(up[r][c]);
            adj[d].push_back(up[r][c+1]);
            adj[d].push_back(up[r+1][c]);
            adj[d].push_back(up[r+1][c+1]);
        }
    }
    
    vector<int> color(total, -1);
    ll ans=0;
    function<void(int)> dfs=[&](int pos){
        if(pos==total){ans++;return;}
        for(int c=0;c<3;c++){
            bool ok=true;
            for(int nb:adj[pos]) if(color[nb]==c){ok=false;break;}
            if(!ok)continue;
            color[pos]=c;
            dfs(pos+1);
            color[pos]=-1;
        }
    };
    dfs(0);
    cout<<ans<<"\n";
}
