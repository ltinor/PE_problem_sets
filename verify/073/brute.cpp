#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll mygcd(ll a,ll b){return b?mygcd(b,a%b):a;}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin>>T;
    while(T--){
        int N;
        cin>>N;

        ll ans=0;
        for(int d=1;d<=N;d++){
            int lo=d/3+1;
            int hi=(d-1)/2;
            for(int n=lo;n<=hi;n++){
                if(mygcd(n,d)==1) ans++;
            }
        }
        cout<<ans<<"\n";
    }
}
