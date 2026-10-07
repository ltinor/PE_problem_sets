#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];

    int n;
    if (mode == "small") {
        n = rand() % 4 + 1; // 1..4
    } else {
        n = rand() % 3 + 5; // 5..7
    }

    cout << n << "\n";
    return 0;
}
