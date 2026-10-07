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
        ll N,a,b;
        cin>>N>>a>>b;

        ll best_n=0,best_d=1;
        for(ll d=1;d<=N;d++){
            // n/d < a/b => n*b < a*d => n = floor((a*d-1)/b)
            ll n=(a*d-1)/b;
            if(n>0 && mygcd(n,d)==1){
                // n/d > best_n/best_d => n*best_d > best_n*d
                if(n*best_d > best_n*d){
                    best_n=n;
                    best_d=d;
                }
            }
        }
        cout<<best_n<<"\n";
    }
}
