#include <bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];

    int B;
    if (mode == "small") {
        B = rand_int(5, 30);
    } else if (mode == "large") {
        B = rand_int(100, 5000);
    } else {
        B = stoi(mode);
    }

    cout << B << "\n";
    return 0;
}
