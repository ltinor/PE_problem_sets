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
        N = rand_int(1, 5);
    } else {
        N = rand_int(5, 20);
    }

    cout << N << "\n";
    for (int i = 0; i < N; i++) {
        int m = rand_int(3, 8);
        cout << m;
        for (int j = 0; j < m; j++) {
            cout << " " << rand_int(1, 200);
        }
        cout << "\n";
    }
    return 0;
}
