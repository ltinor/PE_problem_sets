#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int mygcd(int a,int b){while(b){int t=b;b=a%b;a=t;}return a;}

int main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int R; cin >> R;
    
    vector<pair<int,int>> pts;
    map<pair<int,int>, pair<int,int>> line_sides;
    
    for(int x = -R+1; x < R; x++)
        for(int y = -R+1; y < R; y++)
            if((ll)x*x + (ll)y*y < (ll)R*R && !(x==0 && y==0)){
                pts.push_back({x, y});
                int g = mygcd(abs(x), abs(y));
                int dx = x/g, dy = y/g;
                if(dx < 0 || (dx == 0 && dy < 0)){ dx = -dx; dy = -dy; }
                long double ang = atan2l(y, x);
                bool is_first = (ang <= 0);
                if(is_first) line_sides[{dx, dy}].first++;
                else line_sides[{dx, dy}].second++;
            }
    
    int n = pts.size();
    const long double PI = acosl(-1.0L);
    
    vector<long double> ang(n);
    for(int i = 0; i < n; i++) ang[i] = atan2l(pts[i].second, pts[i].first);
    vector<int> idx(n); iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](int i, int j){ return ang[i] < ang[j]; });
    
    vector<long double> sorted(n);
    for(int i = 0; i < n; i++) sorted[i] = ang[idx[i]];
    for(int i = 0; i < n; i++) sorted.push_back(sorted[i] + 2*PI);
    
    ll total = (ll)n * (n-1) * (n-2) / 6;
    
    // Count bad (≤ PI)
    ll bad = 0;
    const long double EPS = 1e-12L;
    int j = 1;
    for(int i = 0; i < n; i++){
        if(j <= i) j = i + 1;
        long double limit = sorted[i] + PI;
        while(j < i + n && sorted[j] <= limit + EPS) j++;
        ll cnt = j - i - 1;
        if(cnt >= 2) bad += cnt * (cnt - 1) / 2;
    }
    
    // Correction: overcounted triples
    ll correction = 0;
    for(auto& [dir, sides] : line_sides){
        int a = sides.first, b = sides.second;
        long double dir_ang = atan2l(dir.second, dir.first);
        if(dir_ang > 0){
            // positive side (ang>0) is second; negative side (ang-PI<0) is first
            if(b >= 2 && a >= 1) correction += (ll)b * (b-1) * a;
        } else {
            // positive side (ang≤0) is first
            if(a >= 2 && b >= 1) correction += (ll)a * (a-1) * b;
        }
    }
    
    cout << total - (bad - correction) << "\n";
}
