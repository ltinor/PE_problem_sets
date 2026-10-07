#include<bits/stdc++.h>
using namespace std;

int main(){
    long long n;
    cin>>n;

    long long ans=0;

    for(long long i=1;i<n;i++){
        if(i%3==0 || i%5==0)
            ans+=i;
    }

    cout<<ans<<"\n";
}