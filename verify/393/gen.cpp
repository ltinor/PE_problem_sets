#include<bits/stdc++.h>
using namespace std;
#define ll long long
int main(int argc,char* argv[]){
    srand(time(0));
    string mode="small"; if(argc>1)mode=argv[1];
    ll n;
    if(mode=="small")n=2+rand()%2;
    else if(mode=="large")n=4+rand()%2;
    else n=atoll(argv[1]);
    cout<<n<<"\n";
}
