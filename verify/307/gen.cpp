#include<bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];

    int k, n;
    if (mode == "small") {
        k = rand_int(1, 20);
        n = rand_int(k, 30);
    } else {
        k = rand_int(1, 5000);
        n = rand_int(max(k, 1), 500000);
    }

    cout << k << " " << n << "\n";
    return 0;
}
