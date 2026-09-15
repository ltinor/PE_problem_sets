#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];

    ll D, K;
    if (mode == "small") {
        D = rand() % 4 + 1; // 1..4
        K = rand() % min(D, 3LL) + 1;
    } else {
        D = rand() % 6 + 2; // 2..7
        K = rand() % min(D, 4LL) + 1;
    }
    cout << D << " " << K << "\n";
    return 0;
}
