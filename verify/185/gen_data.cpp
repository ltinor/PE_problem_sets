#include<bits/stdc++.h>
using namespace std;
int main(){system("mkdir -p data");
// Use first 11 guesses from PE, truncated to 8 digits
string guesses[]={"56161856","38474396","58554629","97428555","42968496","31742484","45135590","78909715","81573563","26152507","86900958"};
int matches[]={2,1,3,3,3,1,2,3,1,2,3};
for(int i=0;i<10;i++){string fn=string("data/")+(i<9?"0":"")+to_string(i+1)+".in";ofstream f(fn);f<<8<<"\n";for(int j=0;j<8;j++){f<<guesses[j]<<" "<<matches[j]<<"\n";}if(i==0)f<<"56161856 2\n38474396 1\n58554629 3\n";}
}
