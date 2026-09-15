#include<bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    int D;

    if (mode == "small") {
        D = rand_int(1, 500);
    } else if (mode == "large") {
        D = rand_int(2000, 5000);
    } else {
        D = rand_int(1, 5000);
    }

    cout << "1\n" << D << "\n";
}
