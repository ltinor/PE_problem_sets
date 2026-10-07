#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 207: Random generator for check

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    ll a, b;
    if (mode == "small") {
        // Small ratios for quick check
        a = 1;
        b = rand() % 9 + 2; // 1/2 to 1/10
    } else if (mode == "pe") {
        a = 1;
        b = 12345;
    } else {
        a = 1;
        b = rand() % 100 + 10;
    }

    cout << a << " " << b << "\n";
}
