#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
    system("mkdir -p data"); srand(time(0));
    vector<ll> tc(10);
    // 缩数据简单版：所有测试点 N≤8
    tc[0]=8; tc[1]=5; tc[2]=7;
    for(int i=3;i<6;i++)tc[i]=2+rand()%7;   // 2..8
    tc[6]=3; tc[7]=6;
    for(int i=8;i<10;i++)tc[i]=2+rand()%7;  // 2..8
    for(int i=0;i<10;i++){
        char fn[32];sprintf(fn,"data/%02d.in",i+1);
        ofstream f(fn);f<<tc[i]<<"\n";
    }
}
