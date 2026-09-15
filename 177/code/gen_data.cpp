#include<bits/stdc++.h>
using namespace std;
int main(){system("mkdir -p data");
int cases[]={10,10,10,5,5,5,2,2,2,1};
for(int i=0;i<10;i++){string fn=string("data/")+(i<9?"0":"")+to_string(i+1)+".in";ofstream f(fn);f<<cases[i]<<"\n";}
}
