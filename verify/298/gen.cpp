#include<bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];

    int T, M, K;
    if (mode == "small") {
        T = rand() % 10 + 1;
        M = rand() % 3 + 1;
        K = rand() % 5 + 3;
    } else {
        T = rand() % 20 + 5;
        M = rand() % 4 + 2;
        K = rand() % 6 + 5;
    }

    cout << T << " " << M << " " << K << "\n";
    return 0;
}
