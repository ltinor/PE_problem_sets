#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    srand(time(0));
    int S;
    string mode = "small";
    if (argc > 1) mode = argv[1];

    if (mode == "small") {
        S = (rand() % 10 + 1) * 2; // 2,4,...,20
    } else {
        S = (rand() % 95 + 1) * 2 + 10; // 12..200
    }
    cout << S << "\n";
    return 0;
}
