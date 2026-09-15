#include<bits/stdc++.h>
using namespace std;

int rand_int(int l, int r){
    return l + rand() % (r - l + 1);
}

int main(int argc, char* argv[]){
    srand(time(0));

    string mode = "small";
    if(argc > 1) mode = argv[1];

    int N;

    if(mode == "small"){
        N = rand_int(2, 25);
    } else {
        N = rand_int(10, 51);
    }

    assert(N >= 1 && N <= 51);

    cout << N << "\n";
}
