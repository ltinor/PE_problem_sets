#include<bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    long long N;
    if (mode == "small") {
        N = rand_ll(4, 1000);
    } else if (mode == "large") {
        N = rand_ll(10000000, 100000000);
    }

    cout << N << "\n";
    return 0;
}
