#include <bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    int D;
    if (mode == "small") {
        D = rand_int(1, 7);  // brute can handle
    } else if (mode == "large") {
        D = rand_int(8, 100);
    } else {
        D = rand_int(1, 100);
    }

    cout << D << "\n";
    return 0;
}
