#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small"; if (argc > 1) mode = argv[1];
    ll n;
    if (mode == "small") n = 2 + rand() % 5;       // 2..6
    else if (mode == "large") n = 7 + rand() % 2;  // 7..8 (max for brute)
    else n = atoll(argv[1]);
    cout << n << "\n";
}
