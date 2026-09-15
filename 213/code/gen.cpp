#include<bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    int N, R;
    if (mode == "small") {
        N = rand_int(2, 5);
        R = rand_int(1, 5);
    } else if (mode == "pe") {
        N = 30; R = 50;
    } else {
        N = rand_int(2, 10);
        R = rand_int(1, 10);
    }

    cout << N << " " << R << "\n";
}
