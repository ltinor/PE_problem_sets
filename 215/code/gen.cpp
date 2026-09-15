#include<bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    int W, H;
    if (mode == "small") {
        W = rand_int(2, 9);
        H = rand_int(1, min(4, W));
    } else if (mode == "pe") {
        W = 32; H = 10;
    } else {
        W = rand_int(3, 15);
        H = rand_int(1, 5);
    }

    cout << W << " " << H << "\n";
}
