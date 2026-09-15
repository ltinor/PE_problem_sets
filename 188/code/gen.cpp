#include<bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    long long A, B;
    if (mode == "small") {
        A = rand_ll(2, 10);
        B = rand_ll(2, 5);
    } else if (mode == "large") {
        A = rand_ll(100, 2000);
        B = rand_ll(100, 2000);
    }

    cout << A << " " << B << "\n";
    return 0;
}
