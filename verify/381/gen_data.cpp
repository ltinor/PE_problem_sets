#include<bits/stdc++.h>
using namespace std;
int main(){pair<int,int> t[]={{5,20},{5,50},{5,100},{5,200},{5,500},{5,1000},{5,5000},{5,100000},{5,10000000},{5,100000000}};
for(int i=0;i<10;i++){stringstream ss;ss<<"data/"<<setw(2)<<setfill('0')<<(i+1)<<".in";ofstream f(ss.str());f<<t[i].first<<" "<<t[i].second<<"\n";}}
