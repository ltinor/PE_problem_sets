#include<bits/stdc++.h>
using namespace std;

int main(int argc,char* argv[]){
    srand(time(0));
    string mode="small";
    if(argc>1) mode=argv[1];

    long long N; int M;
    if(mode=="small"){
        N=rand()%200+10;
        M=rand()%20+5;
    } else if(mode=="large"){
        N=rand()%5000+5000;
        M=rand()%30+20;
    } else {
        // specific N M
    }

    cout<<N<<" "<<M<<"\n";
}
