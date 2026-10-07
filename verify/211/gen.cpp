#include<bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    int N;
    if (mode == "small") {
        N = rand_int(100, 1000);
    } else if (mode == "pe") {
        N = 64000000;
    } else {
        N = rand_int(1000, 100000);
    }

    cout << N << "\n";
}
