#include <bits/stdc++.h>
using namespace std;
long long rand_ll(long long l,long long r){return l+(long long)(rand())*(long long)(rand())%(r-l+1);}
int main(){system("mkdir -p data");srand(time(0));vector<long long> tc(10);tc[0]=10;for(int i=1;i<3;i++)tc[i]=rand_ll(1,10000);for(int i=3;i<6;i++)tc[i]=rand_ll(1e9,1e12);tc[6]=1;tc[7]=1000000000000LL;for(int i=8;i<10;i++)tc[i]=rand_ll(1,1000000000000LL);for(int i=0;i<10;i++){string fn=string("data/")+(i<9?"0":"")+to_string(i+1)+".in";ofstream f(fn);f<<tc[i]<<"\n";f.close();cout<<"Generated "<<fn<<" n="<<tc[i]<<"\n";}return 0;}
