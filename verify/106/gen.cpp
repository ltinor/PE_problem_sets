#include<bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    int n;
    if (mode == "small") {
        n = rand_int(2, 8);  // brute can handle up to ~8 quickly
    } else if (mode == "large") {
        n = rand_int(9, 12);
    } else {
        n = rand_int(2, 12);
    }

    cout << n << "\n";
    return 0;
}
