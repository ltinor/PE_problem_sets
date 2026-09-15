#include<bits/stdc++.h>
using namespace std;

long long rand_ll(long long l,long long r){
    return l + (long long)(rand() * rand()) % (r - l + 1);
}

// 生成一个 k（第几个三角形数），范围 1..20。
int main(int argc,char* argv[]){
    srand(time(0));

    string mode="small";
    if(argc>1) mode=argv[1];

    long long k;

    if(mode=="small"){
        k = rand_ll(1, 10);
    }
    else if(mode=="large"){
        k = rand_ll(11, 20);
    }
    else {
        k = rand_ll(1, 20);
    }

    assert(k >= 1 && k <= 20);

    cout << k << "\n";
}
