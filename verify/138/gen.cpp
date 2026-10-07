#include<bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    int K;

    if (mode == "small") {
        K = rand_ll(1, 4);
    } else if (mode == "large") {
        K = rand_ll(5, 12);
    }

    assert(K >= 1 && K <= 12);

    cout << K << "\n";
    return 0;
}
