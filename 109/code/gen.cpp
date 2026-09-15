#include<bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    int S;
    if (mode == "small") {
        S = rand_int(3, 50);
    } else if (mode == "large") {
        S = rand_int(100, 171);
    } else {
        S = rand_int(3, 171);
    }

    cout << S << "\n";
    return 0;
}
