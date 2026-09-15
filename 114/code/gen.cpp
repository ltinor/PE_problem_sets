#include <bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    int N, M;
    if (mode == "small") {
        N = rand_int(3, 25);
        M = 3;
    } else if (mode == "large") {
        N = rand_int(26, 50);
        M = rand_int(3, 4);
    } else {
        N = rand_int(3, 50);
        M = rand_int(3, 4);
    }

    cout << N << " " << M << "\n";
    return 0;
}
