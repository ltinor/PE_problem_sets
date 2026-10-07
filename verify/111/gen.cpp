#include <bits/stdc++.h>
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
        n = rand_int(1, 6);
    } else if (mode == "large") {
        n = rand_int(7, 10);
    } else {
        n = rand_int(1, 10);
    }

    cout << n << "\n";
    return 0;
}
