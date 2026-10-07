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

    int n;
    if (mode == "small") {
        n = rand_int(1, 12);        // brute 对拍可承受
    } else if (mode == "large") {
        n = rand_int(13, 24);       // 仅 std 可算
    } else {
        n = rand_int(1, 24);
    }

    cout << n << "\n";
    return 0;
}
