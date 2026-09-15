#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    ll M;
    cin >> M;

    map<pair<int,int>,int> grid;
    int x=0,y=0,dir=0;
    int dx[]={0,1,0,-1};
    int dy[]={-1,0,1,0};
    ll black=0;

    for(ll step=0;step<M;step++){
        auto key=make_pair(x,y);
        int color=grid[key];
        if(color==1){
            grid[key]=0;
            black--;
            dir=(dir+3)%4;
        }else{
            grid[key]=1;
            black++;
            dir=(dir+1)%4;
        }
        x+=dx[dir];
        y+=dy[dir];
    }
    cout<<black<<"\n";
}
