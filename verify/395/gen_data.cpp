#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(){
    system("mkdir -p data"); srand(time(0));
    vector<ll> tc(10);
    tc[0]=5; tc[1]=3; tc[2]=7;
    for(int i=3;i<6;i++)tc[i]=2+rand()%6;
    tc[6]=1; tc[7]=10;
    for(int i=8;i<10;i++)tc[i]=3+rand()%8;
    for(int i=0;i<10;i++){
        char fn[32];sprintf(fn,"data/%02d.in",i+1);
        ofstream f(fn);f<<tc[i]<<"\n";
    }
}
