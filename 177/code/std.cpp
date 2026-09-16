#include<bits/stdc++.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#ifndef M_E
#define M_E 2.71828182845904523536
#endif
using namespace std;
const double EPS=1e-9;

// 177: integer angled quadrilateral
// 5 free params: a1,a2,b1,c1,c2  → derive b2,d1,d2
// Eqs: a2+b1+b2+c1=180  a1+a2+b1+d2=180  a1+c2+d1+d2=180

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int step; cin>>step;
    double s[181]; for(int i=1;i<180;i++) s[i]=sin(i*M_PI/180.0);
    
    set<vector<int>> seen;
    int ans=0;
    
    // a1=CAD, a2=CAB, b1=ABD, c1=BCA, c2=ACD
    for(int a1=step;a1<180;a1+=step)
    for(int a2=step;a2<180;a2+=step)
    for(int b1=step;b1<180;b1+=step)
    for(int c1=step;c1<180;c1+=step)
    for(int c2=step;c2<180;c2+=step){
        // b2 from eq1: 180 - a2 - b1 - c1
        int b2=180-a2-b1-c1;
        if(b2<=0||b2>=180||b2%step!=0)continue;
        // d2 from eq2: 180 - a1 - a2 - b1
        int d2=180-a1-a2-b1;
        if(d2<=0||d2>=180||d2%step!=0)continue;
        // d1 from eq4: 180 - a1 - c2 - d2
        int d1=180-a1-c2-d2;
        if(d1<=0||d1>=180||d1%step!=0)continue;
        // Verify eq3: b2 + c1 + c2 + d1 == 180
        if(b2+c1+c2+d1!=180)continue;
        
        // Convex: all quad angles < 180
        if(a1+a2>=180||b1+b2>=180||c1+c2>=180||d1+d2>=180)continue;
        
        // Sine law consistency
        double p1=s[a1]*s[b1]*s[c1]*s[d1];
        double p2=s[a2]*s[b2]*s[c2]*s[d2];
        if(fabs(p1-p2)>EPS*max(p1,p2))continue;
        
        // Non-similar: normalize by sorted angles
        vector<int> v={a1,a2,b1,b2,c1,c2,d1,d2};
        sort(v.begin(),v.end());
        if(seen.insert(v).second)ans++;
    }
    
    cout<<ans<<"\n";
}
