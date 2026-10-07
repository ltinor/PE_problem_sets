#include<bits/stdc++.h>
using namespace std;

bool is_pandigital(long long num,int n){
    if(num==0) return false;
    string s=to_string(num);
    if((int)s.size()!=n) return false;
    int mask=0;
    for(char c:s){
        int d=c-'0';
        if(d<1 || d>n) return false;
        if(mask&(1<<d)) return false;
        mask|=(1<<d);
    }
    return true;
}

int main(){
    int N;
    cin>>N;
    
    long long best=0;
    
    for(int base=1;base<=99999;base++){
        string concat;
        for(int mul=1;mul<=9;mul++){
            concat+=to_string(base*mul);
            int len=concat.size();
            if(len>N) break;
            if(len==N && mul>=2){
                long long val=stoll(concat);
                if(is_pandigital(val,N) && val>best) best=val;
            }
        }
    }
    
    cout<<best<<"\n";
    return 0;
}
