#include<bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    int N;
    if (mode == "small") {
        N = rand() % 9 + 1; // 1..9
    } else {
        N = rand() % 9 + 1; // same range, just for completeness
    }

    assert(N >= 1 && N <= 9);
    cout << N << "\n";
    return 0;
}
