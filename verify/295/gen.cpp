#include<bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];

    int N;
    if (mode == "small") {
        N = rand() % 10 + 1;
    } else {
        N = rand() % 100 + 10;
    }

    cout << N << "\n";
    return 0;
}
