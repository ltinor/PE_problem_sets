#include<bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    long long n;
    int d;

    if (mode == "small") {
        n = rand_ll(1, 200000);
        d = 1 + rand() % 9;
    } else if (mode == "large") {
        n = rand_ll(1, 100000000000LL);
        d = 1 + rand() % 9;
    }

    assert(n >= 1 && n <= 100000000000LL);
    assert(d >= 1 && d <= 9);

    cout << n << " " << d << "\n";
}
