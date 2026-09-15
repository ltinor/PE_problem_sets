#include<bits/stdc++.h>
using namespace std;

int rand_int(int l, int r){
    return l + rand() % (r - l + 1);
}

int main(int argc, char* argv[]){
    srand(time(0));
    string mode = "small";
    if(argc > 1) mode = argv[1];

    int M, K;
    if(mode == "small"){
        M = rand_int(1, 1000);
        K = rand_int(1, 10);
    } else {
        M = rand_int(1001, 1000000);
        K = rand_int(1, 10);
    }
    cout << M << " " << K << "\n";
}
