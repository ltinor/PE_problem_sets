#include<bits/stdc++.h>
using namespace std;

long long rand_ll(long long l, long long r) {
    return l + (long long)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    long long R;

    if (mode == "small") {
        R = rand_ll(1, 200);
    } else if (mode == "large") {
        R = rand_ll(201, 1000000);
    }

    assert(R >= 1 && R <= 1000000000);

    cout << R << "\n";
    return 0;
}
