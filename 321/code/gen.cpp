#include<bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    int K;
    if (mode == "small") {
        K = rand() % 5 + 1; // 1..5
    } else {
        K = rand() % 10 + 6; // 6..15
    }

    cout << K << "\n";
    return 0;
}
