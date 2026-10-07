#include<bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    int N;

    if (mode == "small") {
        N = rand_int(10, 200);
    } else if (mode == "large") {
        N = rand_int(1000, 1053779);
    } else {
        N = rand_int(10, 1053779);
    }

    assert(N >= 1 && N <= 1053779);

    cout << N << "\n";
    return 0;
}
