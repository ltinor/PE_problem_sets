#include<bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];

    int K;
    if (mode == "small") {
        K = rand_int(1, 3);
    } else {
        K = 35; // PE original
    }
    cout << K << "\n";
    return 0;
}
