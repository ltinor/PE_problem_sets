#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(int argc,char* argv[]){
    srand(time(0));
    string mode="small"; if(argc>1)mode=argv[1];
    ll n;
    // 缩数据简单版：N 限制在 [2,8]，直接模拟即可
    if(mode=="small")n=2+rand()%7;      // 2..8
    else n=2+rand()%7;                  // 2..8
    cout<<n<<"\n";
}
