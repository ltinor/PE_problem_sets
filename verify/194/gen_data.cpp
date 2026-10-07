#include<bits/stdc++.h>
using namespace std;
int main(){system("mkdir -p data");
ofstream("data/01.in")<<"1 0 3\n"; // 24
ofstream("data/02.in")<<"0 2 4\n"; // 92928
ofstream("data/03.in")<<"2 2 3\n"; // 20736
ofstream("data/04.in")<<"1 0 4\n";
ofstream("data/05.in")<<"0 2 5\n";
for(int i=5;i<10;i++){string fn=string("data/")+(i<9?"0":"")+to_string(i+1)+".in";ofstream f(fn);f<<(i%3==0)<<' '<<(i%3)<<' '<<(i+2)<<"\n";}
}
