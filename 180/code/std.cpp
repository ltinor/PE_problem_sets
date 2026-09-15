#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

// 180 simplified: k=-1, solve xy = z(x+y)
// x=a/b, y=c/d → z = ac/(ad+bc) = e/f reduced
// Sum all distinct s = a/b + c/d + e/f

ll mygcd(ll a,ll b){while(b){ll t=b;b=a%b;a=t;}return a;}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int K; cin>>K;
    
    struct Frac{ ll num,den; };
    set<pair<ll,ll>> sums; // store reduced s
    
    for(ll a=1;a<K;a++) for(ll b=a+1;b<=K;b++){
        if(mygcd(a,b)!=1) continue;
        for(ll c=1;c<K;c++) for(ll d=c+1;d<=K;d++){
            if(mygcd(c,d)!=1) continue;
            
            // z = (a/b)*(c/d) / (a/b + c/d) = ac/(ad+bc)
            ll e = a*c;
            ll f = a*d + b*c;
            ll g = mygcd(e,f); e/=g; f/=g;
            
            // Check z is reduced and f ≤ K
            if(f > K) continue;
            if(mygcd(e,f)!=1) continue;
            if(!(e>0 && f>0)) continue;
            
            // Compute s = a/b + c/d + e/f  reduced
            // s = (a*d*f + c*b*f + e*b*d) / (b*d*f)
            ll sn = a*d*f + c*b*f + e*b*d;
            ll sd = b*d*f;
            ll sg = mygcd(sn,sd); sn/=sg; sd/=sg;
            sums.insert({sn,sd});
        }
    }
    
    // Sum all distinct s values (as reduced fractions)
    // Total = Σ sn/sd. Sum over all fractions: compute common denominator
    ll total_num=0, total_den=1;
    for(auto& [n,d] : sums){
        total_num = total_num*d + n*total_den;
        total_den *= d;
        ll g = mygcd(total_num,total_den);
        total_num/=g; total_den/=g;
    }
    cout << total_num + total_den << "\n";
}
