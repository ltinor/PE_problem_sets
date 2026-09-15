#include<bits/stdc++.h>
using namespace std;

bool is_prime(int n){
    if(n<2) return false;
    if(n==2||n==3) return true;
    if(n%2==0||n%3==0) return false;
    for(int i=5;i*i<=n;i+=6)
        if(n%i==0||n%(i+2)==0) return false;
    return true;
}

bool left_truncatable(int n){
    string s=to_string(n);
    int len=s.size();
    for(int i=0;i<len;i++){
        int val=stoi(s.substr(i));
        if(!is_prime(val)) return false;
    }
    return true;
}

int main(){
    int dummy; cin>>dummy;
    
    vector<int> right_trunc={2,3,5,7};
    for(int idx=0;idx<(int)right_trunc.size();idx++){
        int cur=right_trunc[idx];
        for(int d=1;d<=9;d+=2){
            if(d==5) continue;
            int nxt=cur*10+d;
            if(is_prime(nxt))
                right_trunc.push_back(nxt);
        }
    }
    
    long long sum=0;
    for(int x:right_trunc){
        if(x>=10 && left_truncatable(x))
            sum+=x;
    }
    
    cout<<sum<<"\n";
    return 0;
}
