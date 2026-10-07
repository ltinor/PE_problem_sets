#include<bits/stdc++.h>
using namespace std;

long long rand_ll(long long l,long long r){
    return l + (long long)rand()*rand()%(r-l+1);
}

int main(int argc,char* argv[]){
    srand(time(0));

    string mode="small";
    if(argc>1) mode=argv[1];

    long long N;

    if(mode=="small"){
        // N ≤ 100000: brute可以在几秒内完成
        N = rand_ll(2, 100000);
    }
    else if(mode=="large"){
        // N ≤ 5000000: 正解可用memoization快速完成
        N = rand_ll(100000, 5000000);
    }

    assert(N >= 2 && N <= 5000000);

    cout << N << "\n";
}
