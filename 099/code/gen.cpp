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
        N = rand_int(2, 20);
    } else {
        N = rand_int(100, 1000);
    }

    cout << N << "\n";
    for (int i = 0; i < N; i++) {
        int a = rand_int(2, 1000);
        int b = rand_int(2, 1000);
        cout << a << " " << b << "\n";
    }

    return 0;
}
