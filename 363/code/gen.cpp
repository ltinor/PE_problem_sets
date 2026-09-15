#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];

    int steps;
    if (mode == "small") {
        steps = 1000;
    } else if (mode == "large") {
        steps = 100000;
    } else {
        steps = stoi(mode);
    }

    cout << steps << "\n";
    return 0;
}
