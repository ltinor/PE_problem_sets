#include<bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    int n, k;

    if (mode == "small") {
        n = (int)rand_ll(1, 4);
        int ks[3] = {1, 3, 5};
        k = ks[rand() % 3];
    } else if (mode == "large") {
        n = 4;
        k = 5;
    } else {
        n = (int)rand_ll(1, 4);
        int ks[3] = {1, 3, 5};
        k = ks[rand() % 3];
    }

    assert(n >= 1 && n <= 4);
    assert(k == 1 || k == 3 || k == 5);

    cout << n << " " << k << "\n";
}
