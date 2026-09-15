#include<bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));
    
    string mode = "small";
    if (argc > 1) mode = argv[1];
    
    long long N, K;
    
    if (mode == "small") {
        N = rand_ll(10, 1000);
        // K is C(n) for some n; pick a reasonable value
        K = rand_ll(0, 10);
    } else {
        N = rand_ll(1000, 100000);
        K = rand_ll(0, 20);
    }
    
    cout << N << " " << K << "\n";
    return 0;
}
