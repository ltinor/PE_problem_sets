#include<bits/stdc++.h>
using namespace std;
int main(){int t[]={1,2,3,4,5,6,7,30,30,30};
for(int i=0;i<10;i++){stringstream ss;ss<<"data/"<<setw(2)<<setfill('0')<<(i+1)<<".in";ofstream f(ss.str());f<<t[i]<<"\n";}}
