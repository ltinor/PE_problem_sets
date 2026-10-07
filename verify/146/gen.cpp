#include<bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    long long M;

    if (mode == "small") {
        M = rand_ll(100, 100000);
    } else if (mode == "large") {
        M = rand_ll(100001, 5000000);
    }

    assert(M >= 1 && M <= 150000000);

    cout << M << "\n";
    return 0;
}
