#include<bits/stdc++.h>
using namespace std;

int main(int argc,char* argv[]){
    srand(time(0));
    string mode="small";
    if(argc>1) mode=argv[1];

    int A,B;
    if(mode=="small"){
        A=rand()%10+2;
        B=rand()%10+2;
    } else if(mode=="large"){
        A=rand()%50+50;
        B=rand()%50+50;
    } else {
        // specific
    }

    cout<<A<<" "<<B<<"\n";
}
