#include<bits/stdc++.h>
using namespace std;
int main(){system("mkdir -p data");
int cases[]={1,2,3,5,8,13,21,34,55,89};
for(int i=0;i<10;i++){string fn=string("data/")+(i<9?"0":"")+to_string(i+1)+".in";ofstream f(fn);f<<cases[i]<<"\n";}}
