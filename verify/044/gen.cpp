#include<bits/stdc++.h>
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
        M = rand_int(100, 1500);
    } else if (mode == "large") {
        M = rand_int(1500, 3000);
    } else {
        M = rand_int(100, 3000);
    }

    assert(M >= 1 && M <= 3000);
    cout << M << "\n";
}
