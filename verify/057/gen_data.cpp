#include <bits/stdc++.h>
using namespace std;
int main(){system("mkdir -p data");
for (int id=1;id<=10;id++){string fn=string("data/")+(id<10?"0":"")+to_string(id)+".in";
ofstream f(fn);int N;if(id<=3)N=id*3;else if(id<=6)N=id*20;else N=id*100;f<<"1\n"<<N<<"\n";}}