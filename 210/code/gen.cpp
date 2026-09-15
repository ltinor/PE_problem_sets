#include<bits/stdc++.h>
using namespace std;
#define ll long long

// PE 210: Generator for check

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    ll r;
    if (mode == "small") {
        r = rand() % 50 + 1; // small r for brute check
    } else if (mode == "pe") {
        r = 1000000000;
    } else {
        r = rand() % 10000 + 100;
    }

    cout << r << "\n";
}
