#include<bits/stdc++.h>
using namespace std;

long long fact[11];
long long rand_ll(long long l, long long r) {
    return l + (long long)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    fact[0] = 1;
    for (int i = 1; i <= 10; i++) fact[i] = fact[i-1] * i;

    int N;
    long long K;

    if (mode == "small") {
        N = rand_ll(1, 6);
        K = rand_ll(1, fact[N]);
    } else if (mode == "large") {
        N = rand_ll(7, 10);
        K = rand_ll(1, fact[N]);
    } else {
        N = rand_ll(1, 10);
        K = rand_ll(1, fact[N]);
    }

    cout << "1\n" << N << " " << K << "\n";
}
