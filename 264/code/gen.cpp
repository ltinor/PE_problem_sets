#include <bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];

    int P, Hx;
    if (mode == "small") {
        P = rand_int(10, 500);
    } else {
        P = rand_int(500, 10000);
    }
    // Hx must be odd for solutions
    Hx = 2 * rand_int(1, 5) - 1; // 1,3,5,7,9

    cout << P << " " << Hx << "\n";
    return 0;
}
