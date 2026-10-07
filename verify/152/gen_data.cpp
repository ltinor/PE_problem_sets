#include<bits/stdc++.h>
using namespace std;
int main(){system("mkdir -p data");
int cases[]={5,10,15,20,25,30,32,35,38,40};
for(int i=0;i<10;i++){string fn=string("data/")+(i<9?"0":"")+to_string(i+1)+".in";ofstream f(fn);f<<cases[i]<<"\n";}}
