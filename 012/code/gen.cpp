#include<bits/stdc++.h>
using namespace std;

long long rand_ll(long long l,long long r){
    return l + (long long)rand()*rand()%(r-l+1);
}

int main(int argc,char* argv[]){
    srand(time(0));

    string mode="small";
    if(argc>1) mode=argv[1];

    int K;

    if(mode=="small"){
        // K ≤ 1000: 可在合理时间内暴力验证
        K = rand_ll(1, 1000);
    }
    else if(mode=="large"){
        // K ≤ 5000: 正解仍可在约1秒内完成
        K = rand_ll(1000, 5000);
    }

    assert(K >= 1 && K <= 5000);

    cout << K << "\n";
}
