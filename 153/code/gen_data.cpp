#include<bits/stdc++.h>
using namespace std;
int main(){system("mkdir -p data");
long long cases[]={1,2,5,10,50,100,500,1000,10000,100000};
for(int i=0;i<10;i++){string fn=string("data/")+(i<9?"0":"")+to_string(i+1)+".in";ofstream f(fn);f<<cases[i]<<"\n";}}
