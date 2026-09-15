#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];
    ll n, k;
    if (mode == "small") { n = 5; k = 3; }
    else if (mode == "medium") { n = 20; k = 10; }
    else if (mode == "large") { n = 100; k = 50; }
    else { n = atoll(argv[1]); k = atoll(argv[2]); }
    cout << n << " " << k << "\n";
}
