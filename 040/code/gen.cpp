#include<bits/stdc++.h>
using namespace std;

int rand_int(int l,int r){
    return l+rand()%(r-l+1);
}

int main(int argc,char* argv[]){
    srand(time(0));
    
    string mode="small";
    if(argc>1) mode=argv[1];
    
    int K;
    if(mode=="small"){
        K=rand_int(1,3);
    } else {
        K=rand_int(1,7);
    }
    
    cout<<K;
    for(int i=0;i<K;i++){
        int p=rand_int(1,1000000);
        cout<<" "<<p;
    }
    cout<<"\n";
    return 0;
}
