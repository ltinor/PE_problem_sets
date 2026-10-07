#include<bits/stdc++.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];

    int D;
    if (mode == "small") {
        D = rand_int(10, 12); // min for pandigital is 10
    } else {
        D = rand_int(20, 40);
    }
    cout << D << "\n";
    return 0;
}
