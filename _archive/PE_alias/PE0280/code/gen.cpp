#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];

    int G;
    if (mode == "small") {
        G = 1 + rand() % 2; // 1 or 2
    } else if (mode == "large") {
        G = 5;
    } else {
        G = stoi(mode);
    }

    cout << G << "\n";
    return 0;
}
