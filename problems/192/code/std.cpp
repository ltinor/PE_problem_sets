#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 i128;

// Continued fraction of sqrt(S): [a0; a1, a2, ..., a_{L-1}, 2*a0] periodic
// Convergents p_k/q_k approach sqrt(S). Best approximation for bound D
// is the last convergent with q ≤ D.

void solve_sqrt(ll S, ll D, ll& sum_denom){
    if(S==0)return;
    ll a0=(ll)sqrt(S);
    if(a0*a0==S)return; // perfect square
    
    // Compute period
    ll m=0, d=1, a=a0;
    vector<ll> cf; cf.push_back(a0);
    while(a!=2*a0){
        m=d*a-m;
        d=(S-m*m)/d;
        a=(a0+m)/d;
        cf.push_back(a);
    }
    int L=cf.size()-1; // period length
    
    // Generate convergents for up to D bound
    // p_{-2}=0, p_{-1}=1, q_{-2}=1, q_{-1}=0
    ll p_2=0, p_1=1, q_2=1, q_1=0;
    ll best_p=0, best_q=0;
    
    for(int i=0;;i++){
        ll ai=cf[i%cf.size()];
        if(i>0 && i%cf.size()==0) ai=cf[0]; // handle first term vs period
        
        ll p=ai*p_1+p_2;
        ll q=ai*q_1+q_2;
        
        if(q>D) break;
        best_p=p; best_q=q;
        
        p_2=p_1; p_1=p;
        q_2=q_1; q_1=q;
    }
    
    if(best_q>0) sum_denom+=best_q;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int N; cin>>N;
    ll D=1000000000000LL; // 10^12
    ll sum=0;
    for(int n=2;n<=N;n++){
        solve_sqrt(n,D,sum);
    }
    cout<<sum<<"\n";
}
