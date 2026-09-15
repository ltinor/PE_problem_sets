#include<bits/stdc++.h>
using namespace std;
int main(){pair<int,int> t[]={{1,1},{2,2},{3,4},{9,12},{100,500},{2,3},{3,3},{4,4},{1,10},{10,1}};
for(int i=0;i<10;i++){stringstream ss;ss<<"data/"<<setw(2)<<setfill('0')<<(i+1)<<".in";ofstream f(ss.str());f<<t[i].first<<" "<<t[i].second<<"\n";}}
