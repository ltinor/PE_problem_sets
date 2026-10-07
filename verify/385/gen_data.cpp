#include<bits/stdc++.h>
using namespace std;
int main(){ll t[]={4,6,8,10,20,50,100,1000,1000000000,1000000000};
for(int i=0;i<10;i++){stringstream ss;ss<<"data/"<<setw(2)<<setfill('0')<<(i+1)<<".in";ofstream f(ss.str());f<<t[i]<<"\n";}}
