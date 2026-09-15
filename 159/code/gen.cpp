#include<bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    int N;
    if (mode == "small") {
        N = rand_ll(2, 10000);
    } else if (mode == "large") {
        N = rand_ll(100000, 999999);
    }

    assert(N >= 2 && N <= 999999);
    cout << N << "\n";
}
