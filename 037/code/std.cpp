#include<bits/stdc++.h>
using namespace std;
#define ll long long

bool is_prime(int n){
    if(n<2) return false;
    if(n==2) return true;
    if(n%2==0) return false;
    for(int i=3;i*i<=n;i+=2)
        if(n%i==0) return false;
    return true;
}

bool left_truncatable(int n){
    if(n<10) return is_prime(n);
    string s=to_string(n);
    for(int i=0;i<(int)s.size();i++){
        int val=stoi(s.substr(i));
        if(!is_prime(val)) return false;
    }
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int dummy; cin>>dummy;
    
    vector<int> right_trunc={2,3,5,7};
    queue<int> q;
    for(int x:right_trunc) q.push(x);
    int digits[]={1,3,7,9};
    
    while(!q.empty()){
        int cur=q.front(); q.pop();
        for(int d:digits){
            int nxt=cur*10+d;
            if(is_prime(nxt)){
                right_trunc.push_back(nxt);
                q.push(nxt);
            }
        }
    }
    
    ll sum=0;
    for(int x:right_trunc){
        if(x>=10 && left_truncatable(x))
            sum+=x;
    }
    
    cout<<sum<<"\n";
    return 0;
}
