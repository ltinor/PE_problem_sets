#include<bits/stdc++.h>
using namespace std;
int main(){pair<int,int> t[]={{2,5},{2,10},{2,15},{2,20},{2,25},{2,30},{2,35},{2,40},{2,45},{2,45}};
for(int i=0;i<10;i++){stringstream ss;ss<<"data/"<<setw(2)<<setfill('0')<<(i+1)<<".in";ofstream f(ss.str());f<<t[i].first<<" "<<t[i].second<<"\n";}}
