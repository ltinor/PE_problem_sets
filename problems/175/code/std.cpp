#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll mygcd(ll a,ll b){while(b){ll t=b;b=a%b;a=t;}return a;}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    ll a,b; cin>>a>>b;
    ll g=mygcd(a,b); a/=g; b/=g;
    
    vector<ll> runs;
    ll total_steps=0;
    
    while(!(a==1 && b==1)){
        if(a > b){
            ll k = (a - 1) / b;
            a -= k * b;
            runs.push_back(k);
            total_steps += k;
        } else {
            ll k = (b - 1) / a;
            b -= k * a;
            runs.push_back(k);
            total_steps += k;
        }
    }
    
    reverse(runs.begin(), runs.end());
    
    // Leading 1: merges if last original step was L (total_steps is odd)
    // If even (last step was R), insert new leading element
    if(total_steps % 2 == 0){
        runs.insert(runs.begin(), 1); // separate leading 1
    } else {
        if(!runs.empty()) runs[0]++; // merge with first run
        else runs.push_back(1);
    }
    
    for(size_t i=0; i<runs.size(); i++){
        if(i) cout<<",";
        cout<<runs[i];
    }
    cout<<"\n";
}
