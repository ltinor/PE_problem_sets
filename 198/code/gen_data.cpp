#include<bits/stdc++.h>
using namespace std;
int main(){system("mkdir -p data");
int cases[]={50,100,150,200,300,400,500,600,800,1000};
for(int i=0;i<10;i++){string fn=string("data/")+(i<9?"0":"")+to_string(i+1)+".in";ofstream f(fn);f<<cases[i]<<"\n";}
}
