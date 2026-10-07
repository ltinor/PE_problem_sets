#include<bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    srand((unsigned)time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    int D;

    if (mode == "small") {
        // Small D that brute can handle (≤7 for brute, ≤9 for std)
        D = rand() % 6 + 1; // 1..6
    } else if (mode == "large") {
        D = rand() % 3 + 7; // 7..9
    }

    assert(D >= 1 && D <= 9);

    cout << D << "\n";
    return 0;
}
