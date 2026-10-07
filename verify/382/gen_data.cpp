#include<bits/stdc++.h>
using namespace std;
using ll=long long;int main(){ll t[]={3,5,10,15,20,25,25,25,1000000000000000000LL,1000000000000000000LL};
for(int i=0;i<10;i++){stringstream ss;ss<<"data/"<<setw(2)<<setfill('0')<<(i+1)<<".in";ofstream f(ss.str());f<<t[i]<<"\n";}}
