#include<bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    int n;
    long long target;

    if (mode == "small") {
        n = rand_int(2, 20);
        // Generate a target by picking r and computing s
        // For simplicity in check.sh, we output n and target
        target = rand_int(-10000, 10000);
    } else {
        n = rand_int(100, 1000);
        target = (long long)rand_int(-100000000, 100000000);
    }

    cout << n << " " << target << "\n";
    return 0;
}
