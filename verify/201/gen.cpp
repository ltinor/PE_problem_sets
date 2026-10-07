#include<bits/stdc++.h>
using namespace std;

int rand_int(int l, int r){
    return l + rand() % (r - l + 1);
}

int main(int argc, char* argv[]){
    srand(time(0));

    string mode = "small";
    if(argc > 1) mode = argv[1];

    int N, K;

    if(mode == "small"){
        // Small: N ≤ 20 for brute force verification
        N = rand_int(4, 20);
        K = rand_int(1, N/2);
    } else {
        N = rand_int(10, 50);
        K = rand_int(1, N/2);
    }

    assert(N >= 1 && N <= 50);
    assert(K >= 1 && K <= N/2);

    cout << N << " " << K << "\n";
}
