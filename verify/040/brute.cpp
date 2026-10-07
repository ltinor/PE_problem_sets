#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Pre-build Champernowne string up to 10^6
    string s;
    for(int i=1;(int)s.size()<=1000000;i++)
        s+=to_string(i);
    
    int K;
    while(cin>>K){
        long long prod=1;
        for(int i=0;i<K;i++){
            int p;
            cin>>p;
            prod*=(s[p-1]-'0');
        }
        cout<<prod<<"\n";
    }
    
    return 0;
}
