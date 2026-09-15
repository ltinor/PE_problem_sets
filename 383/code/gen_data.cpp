#include<bits/stdc++.h>
using namespace std;
int main(){ll t[]={10,100,1000,5000,10000,50000,100000,1000000000LL,1000000000000000000LL,1000000000000000000LL};
for(int i=0;i<10;i++){stringstream ss;ss<<"data/"<<setw(2)<<setfill('0')<<(i+1)<<".in";ofstream f(ss.str());f<<t[i]<<"\n";}}
