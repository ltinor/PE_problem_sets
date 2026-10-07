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
        N = rand_ll(1, 4);
    } else if (mode == "large") {
        N = rand_ll(5, 9);
    }

    assert(N >= 1 && N <= 9);
    cout << N << "\n";
}
