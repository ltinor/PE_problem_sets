#include<bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];

    int N;
    if (mode == "small") {
        N = rand() % 40 + 5;       // 5..44   (for std vs brute cross-check)
    } else {
        N = rand() % 2000 + 100;   // 100..2099 (for std timing)
    }

    cout << N << "\n";
    return 0;
}
