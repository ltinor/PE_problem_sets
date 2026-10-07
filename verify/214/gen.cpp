#include<bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    int N, L;
    if (mode == "small") {
        N = rand_int(10, 1000);
        L = rand_int(3, 8);
    } else if (mode == "pe") {
        N = 40000000;
        L = 25;
    } else {
        N = rand_int(1000, 100000);
        L = rand_int(5, 15);
    }

    cout << N << " " << L << "\n";
}
