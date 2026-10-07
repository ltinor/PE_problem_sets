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
        n = rand_ll(3,15);
    }
    else if(mode=="large"){
        n = rand_ll(13,15);
    }

    assert(n >= 3 && n <= 15);

    cout << n << "\n";
}
