#include <bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    int M;
    if (mode == "small") {
        M = rand_int(3, 100);
    } else if (mode == "large") {
        M = rand_int(500, 1000);
    } else {
        M = rand_int(3, 1000);
    }

    cout << "1\n" << M << "\n";
    return 0;
}
