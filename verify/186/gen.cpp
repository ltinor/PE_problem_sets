#include<bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    int P, T;
    if (mode == "small") {
        P = rand_ll(1, 50);
        T = rand_ll(0, 999999);
    } else if (mode == "large") {
        P = rand_ll(90, 100);
        T = 524287;
    }

    cout << P << " " << T << "\n";
    return 0;
}
