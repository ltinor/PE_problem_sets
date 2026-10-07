#include<bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if(argc > 1) mode = argv[1];

    int D;
    if(mode == "small") D = rand_ll(1, 5);
    else D = rand_ll(6, 16);

    assert(D >= 1 && D <= 16);
    cout << D << "\n";
}
