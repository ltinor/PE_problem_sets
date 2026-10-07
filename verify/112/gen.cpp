#include <bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    int P;
    if (mode == "small") {
        P = rand_int(1, 60);
    } else if (mode == "large") {
        P = rand_int(80, 99);
    } else {
        P = rand_int(1, 99);
    }

    cout << P << "\n";
    return 0;
}
