#include<bits/stdc++.h>
using namespace std;

long long rand_ll(long long l,long long r){
    return l + (long long)rand()*rand()%(r-l+1);
}

int main(int argc,char* argv[]){
    srand(time(0));

    string mode="small";
    if(argc>1) mode=argv[1];

    long long n;

    if(mode=="small"){
        n = rand_ll(2,1e6);
    }
    else if(mode=="large"){
        n = rand_ll(2,1e9);
    }

    assert(n >= 2 && n <= 1e9);

    cout << n << "\n";
}