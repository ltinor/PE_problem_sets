#include<bits/stdc++.h>
using namespace std;
int main(){system("mkdir -p data");
int cases[]={1,2,3,4};
for(int i=0;i<4;i++){string fn=string("data/")+(i<9?"0":"")+to_string(i+1)+".in";ofstream f(fn);f<<cases[i]<<"\n";}
srand(time(0));
for(int i=4;i<10;i++){int r=rand()%3+1;string fn=string("data/")+(i<9?"0":"")+to_string(i+1)+".in";ofstream f(fn);f<<r<<"\n";}
}
