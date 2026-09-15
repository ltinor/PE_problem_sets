#include <bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    int K;

    if (mode == "small") {
        K = rand_int(0, 2);
    } else if (mode == "large") {
        K = rand_int(2, 4);
    }

    cout << K << "\n";
    return 0;
}
