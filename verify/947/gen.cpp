#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0) ^ getpid());

    string mode = "small";
    if (argc > 1) mode = argv[1];

    int M;
    if (mode == "small") {
        M = rand_int(1, 100);        // brute 对拍可承受
    } else if (mode == "large") {
        M = rand_int(101, 1000);     // 仅 std 可算
    } else {
        M = rand_int(1, 1000);
    }

    cout << M << "\n";
    return 0;
}
