#include<bits/stdc++.h>
using namespace std;

// 暴力参考实现：直接枚举 n 的所有因数 d，对每个因数算 Ω(d)。
long long omega(long long x){
    long long cnt=0;
    for(long long p=2;p*p<=x;p++){
        while(x%p==0){ x/=p; cnt++; }
    }
    if(x>1) cnt++;
    return cnt;
}

int main(){
    long long n,m;
    cin>>n>>m;

    long long ans=0;
    for(long long d=1;d<=n;d++){
        if(n%d==0){
            if(omega(d)%m==0) ans+=d;
        }
    }

    cout<<ans<<"\n";
}
