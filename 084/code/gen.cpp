#include<bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r){
    return l + (long long)rand()*rand()%(r-l+1);
}

int main(int argc, char* argv[]){
    srand(time(0));

    string mode = "small";
    if(argc > 1) mode = argv[1];

    int S;

    if(mode == "small"){
        S = rand_ll(4, 6);
    }

    assert(S >= 4 && S <= 6);

    cout << S << "\n";
}
