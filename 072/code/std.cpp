#include<bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN=1000000;

int phi[MAXN+5];
ll pref[MAXN+5];

void init(){
    for(int i=1;i<=MAXN;i++) phi[i]=i;
    for(int i=2;i<=MAXN;i++){
        if(phi[i]==i){
            for(int j=i;j<=MAXN;j+=i){
                phi[j]-=phi[j]/i;
            }
        }
    }
    pref[0]=0;
    for(int i=1;i<=MAXN;i++){
        pref[i]=pref[i-1]+phi[i];
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();

    int T;
    cin>>T;
    while(T--){
        int N;
        cin>>N;
        // sum phi(2..N) = pref[N] - phi[1] = pref[N] - 1
        cout<<pref[N]-1<<"\n";
    }
}
