#include<bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    int n;
    if (mode == "small") {
        n = rand_ll(1, 100);
    } else if (mode == "large") {
        n = rand_ll(1, 10000);
    }

    assert(n >= 1 && n <= 10000);

    cout << "1\n" << n << "\n";
}
