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
        M = rand_int(2, 100);
    } else if (mode == "large") {
        M = rand_int(900000, 1000000);
    }

    assert(M >= 2 && M <= 1000000);

    cout << M << "\n";
}
