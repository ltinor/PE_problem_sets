#include<bits/stdc++.h>
using namespace std;

// Big integer represented as vector<int> in base 10, least significant first
vector<int> add_big(vector<int> a, vector<int> b){
    vector<int> res;
    int carry=0;
    for(size_t i=0;i<max(a.size(),b.size())||carry;i++){
        int sum=carry;
        if(i<a.size()) sum+=a[i];
        if(i<b.size()) sum+=b[i];
        res.push_back(sum%10);
        carry=sum/10;
    }
    return res;
}

vector<int> reverse_big(const vector<int>& a){
    vector<int> b=a;
    reverse(b.begin(),b.end());
    return b;
}

bool is_palindrome(const vector<int>& a){
    int L=a.size();
    for(int i=0;i<L/2;i++) if(a[i]!=a[L-1-i]) return false;
    return true;
}

vector<int> to_big(long long x){
    vector<int> res;
    if(x==0) return {0};
    while(x){res.push_back(x%10);x/=10;}
    return res;
}

bool is_lychrel(long long n, int M){
    vector<int> cur=to_big(n);
    for(int it=0;it<M;it++){
        vector<int> rev=reverse_big(cur);
        cur=add_big(cur,rev);
        if(is_palindrome(cur)) return false;
    }
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long N; int M;
    cin>>N>>M;
    int cnt=0;
    for(long long i=1;i<N;i++){
        if(is_lychrel(i,M)) cnt++;
    }
    cout<<cnt<<"\n";
}
