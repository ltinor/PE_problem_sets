#include<bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    int T;
    if (mode == "small") {
        T = rand_int(1, 5);
    } else {
        T = rand_int(1, 10);
    }

    cout << T << "\n";
    for (int i = 0; i < T; i++) {
        int B, W;
        if (mode == "small") {
            B = rand_int(0, 8);
            W = rand_int(0, 6);
        } else {
            B = rand_int(0, 60);
            W = rand_int(0, 40);
        }
        cout << B << " " << W << "\n";
    }

    return 0;
}
