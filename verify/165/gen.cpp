#include<bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if(argc > 1) mode = argv[1];

    int N;
    if(mode == "small") N = rand_ll(1, 50);
    else N = rand_ll(100, 5000);

    assert(N >= 1 && N <= 5000);
    cout << N << "\n";
}
