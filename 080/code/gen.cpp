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
        N = rand_int(2, 10);
    } else if (mode == "large") {
        N = rand_int(80, 100);
    }

    assert(N >= 2 && N <= 100);

    cout << N << "\n";
}
