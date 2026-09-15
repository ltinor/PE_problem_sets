#include <bits/stdc++.h>
using namespace std;
int main(){system("mkdir -p data");
for(int id=1;id<=10;id++){string fn=string("data/")+(id<10?"0":"")+to_string(id)+".in";
ofstream f(fn);string msg="Hello World! This is test "+to_string(id)+".";
vector<int>c;for(char ch:msg)c.push_back(ch^('a'+id%26));
f<<c.size()<<"\n";for(size_t i=0;i<c.size();i++)f<<c[i]<<" \n"[i+1==c.size()];}}