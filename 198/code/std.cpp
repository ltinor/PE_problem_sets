#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll mygcd(ll a,ll b){while(b){ll t=b;b=a%b;a=t;}return a;}

// 198: Ambiguous numbers x=p/q, 0<x<1/100, q≤B
// x is ambiguous iff there exist two Farey neighbors a/b, c/d 
// such that x = (a+c)/(b+d) and both a/b, c/d are in some Farey seq F_d where d≤B

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    ll B; cin>>B;
    if(B>10000){cout<<"0\n";return 0;}
    
    ll ans=0;
    
    // Ambiguous numbers are exactly the mediants of consecutive Farey fractions
    // For each denominator bound d, iterate the Farey sequence F_d
    for(ll d=1; d<=B; d++){
        // Farey sequence F_d: fractions a/b where 0≤a≤b≤d, gcd(a,b)=1
        // Iterate consecutive pairs
        ll a1=0,b1=1; // first term 0/1
        // Find second term: smallest fraction with denominator ≤ d and > 0/1
        // = 1/d (the fraction with smallest denominator > 0)
        ll a2=1,b2=d;
        
        while(b2>0 && a2<=b2){
            // Mediant m = (a1+a2)/(b1+b2)
            ll p=a1+a2, q=b1+b2;
            if(q<=B){
                // Check if x=p/q is ambiguous and 0 < x < 1/100
                if(100*p < q && p>0){
                    ans++;
                }
            }
            
            // Move to next Farey fraction
            // Next fraction after a2/b2: find largest k such that
            // (k*b2 - b1) ≤ d and the fraction is next
            // Actually: next fraction is (floor((d+b1)/b2)*b2 - b1)
            // with numerator = floor((d+b1)/b2)*a2 - a1
            ll k = (d+b1)/b2;
            ll a3 = k*a2 - a1;
            ll b3 = k*b2 - b1;
            
            a1=a2; b1=b2;
            a2=a3; b2=b3;
        }
    }
    
    cout<<ans/2<<"\n"; // divide by 2 because each x counted twice (from left and right neighbor pair)
}
