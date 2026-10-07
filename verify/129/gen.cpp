#include<bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    int T;

    if (mode == "small") {
        T = rand_ll(1, 100);
    } else if (mode == "large") {
        T = rand_ll(10000, 1000000);
    }

    assert(T >= 1 && T <= 1000000);

    cout << T << "\n";
    return 0;
}
