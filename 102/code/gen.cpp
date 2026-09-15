#include <bits/stdc++.h>
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
        N = rand_int(1, 10);
    } else {
        N = rand_int(10, 100);
    }

    cout << N << "\n";
    for (int i = 0; i < N; i++) {
        int x1 = rand_int(-1000, 1000);
        int y1 = rand_int(-1000, 1000);
        int x2 = rand_int(-1000, 1000);
        int y2 = rand_int(-1000, 1000);
        int x3 = rand_int(-1000, 1000);
        int y3 = rand_int(-1000, 1000);
        cout << x1 << " " << y1 << " " << x2 << " " << y2 << " " << x3 << " " << y3 << "\n";
    }
    return 0;
}
