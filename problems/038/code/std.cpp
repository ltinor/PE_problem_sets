#include<bits/stdc++.h>
using namespace std;

bool is_pandigital(const string &s,int n){
    if((int)s.size()!=n) return false;
    vector<bool> seen(n+1,false);
    for(char c:s){
        int d=c-'0';
        if(d<1 || d>n || seen[d]) return false;
        seen[d]=true;
    }
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N;
    cin>>N;
    
    long long best=0;
    
    for(int base=1;base<=99999;base++){
        string concat;
        for(int n=1;n<=9;n++){
            concat+=to_string(base*n);
            if(concat.size()>(size_t)N) break;
            if(concat.size()==(size_t)N && n>=2){
                if(is_pandigital(concat,N)){
                    long long val=stoll(concat);
                    if(val>best) best=val;
                }
            }
        }
    }
    
    cout<<best<<"\n";
    return 0;
}
