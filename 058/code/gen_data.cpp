#include <bits/stdc++.h>
using namespace std;
int main(){system("mkdir -p data");
for(int id=1;id<=10;id++){string fn=string("data/")+(id<10?"0":"")+to_string(id)+".in";
ofstream f(fn);int P=id<=3?id*5:id<=6?15+id*2:30+id;f<<P<<"\n";}}