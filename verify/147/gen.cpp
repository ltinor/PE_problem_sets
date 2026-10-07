#include<bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    int W, H;

    if (mode == "small") {
        W = rand_ll(1, 5);
        H = rand_ll(1, 5);
    } else if (mode == "large") {
        W = rand_ll(6, 20);
        H = rand_ll(6, 20);
    }

    assert(W >= 1 && W <= 47);
    assert(H >= 1 && H <= 43);

    cout << W << " " << H << "\n";
    return 0;
}
