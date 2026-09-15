#include<bits/stdc++.h>
using namespace std;
int main(){system("mkdir -p data");
int cases[]={8,9,10,15,20,30,40,50,75,100};
for(int i=0;i<10;i++){string fn=string("data/")+(i<9?"0":"")+to_string(i+1)+".in";ofstream f(fn);f<<cases[i]<<"\n";}
}
