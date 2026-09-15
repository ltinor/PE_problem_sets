#include<bits/stdc++.h>
using namespace std;

int digit_at(int pos){
    long long len=1,count=9,start=1;
    while(pos>len*count){
        pos-=len*count;
        len++;
        count*=10;
        start*=10;
    }
    long long num=start+(pos-1)/len;
    int digit_pos=(pos-1)%len;
    string s=to_string(num);
    return s[digit_pos]-'0';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int K;
    while(cin>>K){
        long long prod=1;
        for(int i=0;i<K;i++){
            int p;
            cin>>p;
            prod*=digit_at(p);
        }
        cout<<prod<<"\n";
    }
    
    return 0;
}
