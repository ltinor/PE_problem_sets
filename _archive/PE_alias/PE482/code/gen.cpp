#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];
    ll n;
    if (mode == "small") n = 3;
    else if (mode == "medium") n = 10;
    else if (mode == "large") n = 30;
    else n = atoll(argv[1]);
    cout << n << "\n";
}
