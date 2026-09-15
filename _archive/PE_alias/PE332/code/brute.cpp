#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE332 brute: same as std but simpler, for verification
// Uses double instead of long double for brute comparison

struct Pt { ll x,y,z; };
Pt cross(const Pt& a,const Pt& b){return {a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x};}
ll dot(const Pt& a,const Pt& b){return a.x*b.x+a.y*b.y+a.z*b.z;}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cout<<fixed<<setprecision(6);
    
    int R; cin>>R;
    double total=0.0;
    
    for(int rad=1;rad<=R;rad++){
        ll r2=(ll)rad*rad;
        vector<Pt> pts;
        for(ll x=-rad;x<=rad;x++){
            ll x2=x*x; if(x2>r2)continue;
            for(ll y=-rad;y<=rad;y++){
                ll y2=y*y; ll s=x2+y2; if(s>r2)continue;
                ll z2=r2-s;
                ll z=(ll)round(sqrt((double)z2));
                if(z*z==z2){
                    pts.push_back({x,y,z});
                    if(z!=0)pts.push_back({x,y,-z});
                }
            }
        }
        sort(pts.begin(),pts.end(),[](const Pt&a,const Pt&b){
            if(a.x!=b.x)return a.x<b.x;
            if(a.y!=b.y)return a.y<b.y;
            return a.z<b.z;
        });
        pts.erase(unique(pts.begin(),pts.end(),[](const Pt&a,const Pt&b){
            return a.x==b.x&&a.y==b.y&&a.z==b.z;
        }),pts.end());
        
        int n=(int)pts.size();
        if(n<3)continue;
        double min_area=1e30;
        bool found=false;
        
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                Pt cp=cross(pts[i],pts[j]);
                for(int k=j+1;k<n;k++){
                    if(dot(cp,pts[k])==0)continue;
                    
                    // spherical triangle area via angles
                    double r=rad, ri=1.0/r;
                    double x1=pts[i].x*ri,y1=pts[i].y*ri,z1=pts[i].z*ri;
                    double x2=pts[j].x*ri,y2=pts[j].y*ri,z2=pts[j].z*ri;
                    double x3=pts[k].x*ri,y3=pts[k].y*ri,z3=pts[k].z*ri;
                    
                    auto cn=[&](double ax,double ay,double az,double bx,double by,double bz)->tuple<double,double,double>{
                        double cx=ay*bz-az*by, cy=az*bx-ax*bz, cz=ax*by-ay*bx;
                        double l=sqrt(cx*cx+cy*cy+cz*cz);
                        return {cx/l,cy/l,cz/l};
                    };
                    
                    auto[nx1,ny1,nz1]=cn(x2,y2,z2,x3,y3,z3);
                    auto[nx2,ny2,nz2]=cn(x3,y3,z3,x1,y1,z1);
                    auto[nx3,ny3,nz3]=cn(x1,y1,z1,x2,y2,z2);
                    
                    auto ang=[&](double a,double b,double c,double d,double e,double f){
                        double dt=a*d+b*e+c*f;
                        dt=max(-1.0,min(1.0,dt));
                        return acos(-dt);
                    };
                    
                    double A=ang(nx2,ny2,nz2,nx3,ny3,nz3);
                    double B=ang(nx3,ny3,nz3,nx1,ny1,nz1);
                    double C=ang(nx1,ny1,nz1,nx2,ny2,nz2);
                    
                    double area=(A+B+C-M_PI)*r*r;
                    if(area<min_area){min_area=area;found=true;}
                }
            }
        }
        if(found)total+=min_area;
    }
    cout<<total<<"\n";
}
