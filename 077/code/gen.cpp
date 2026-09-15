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
        K = rand_int(1, 100);
    } else if (mode == "large") {
        K = rand_int(4000, 5000);
    }

    assert(K >= 1 && K <= 5000);

    cout << K << "\n";
}
