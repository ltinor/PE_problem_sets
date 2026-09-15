#include<bits/stdc++.h>
using namespace std;

// Big integer multiplication: multiply big number by small int
vector<int> multiply_big(const vector<int>& a, int b){
    vector<int> res;
    int carry=0;
    for(size_t i=0;i<a.size()||carry;i++){
        long long prod=carry;
        if(i<a.size()) prod+=(long long)a[i]*b;
        res.push_back(prod%10);
        carry=prod/10;
    }
    return res;
}

// a^b for big integer
vector<int> power_big(int a, int b){
    vector<int> res={1};
    for(int i=0;i<b;i++){
        res=multiply_big(res,a);
    }
    return res;
}

int digit_sum(const vector<int>& a){
    int s=0;
    for(int d:a) s+=d;
    return s;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int A,B;
    cin>>A>>B;

    int ans=0;
    for(int a=1;a<A;a++){
        for(int b=1;b<B;b++){
            vector<int> p=power_big(a,b);
            int s=digit_sum(p);
            if(s>ans) ans=s;
        }
    }
    cout<<ans<<"\n";
}
