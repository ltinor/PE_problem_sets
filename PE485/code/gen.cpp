#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];
    ll u, k;
    if (mode == "small") { u = 10; k = 3; }
    else if (mode == "medium") { u = 100; k = 10; }
    else if (mode == "large") { u = 1000; k = 100; }
    else { u = atoll(argv[1]); k = atoll(argv[2]); }
    cout << u << " " << k << "\n";
}
