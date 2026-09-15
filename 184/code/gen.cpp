#include<bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    int T;
    if (mode == "small") {
        T = rand_int(1, 3);
    } else {
        T = rand_int(1, 5);
    }

    cout << T << "\n";
    for (int i = 0; i < T; i++) {
        int R;
        if (mode == "small") {
            R = rand_int(2, 6);  // small R for brute (R=6 has ~100 points)
        } else {
            R = rand_int(2, 50);
        }
        cout << R << "\n";
    }

    return 0;
}
