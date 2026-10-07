#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];
    ll n;
    if (mode == "small") n = rand() % 50 + 1;
    else n = rand() % 500 + 50;
    cout << n << "\n";
    return 0;
}
