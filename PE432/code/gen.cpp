#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small"; if (argc > 1) mode = argv[1];
    if (mode == "pe") cout << "510510 100000000000\n";
    else if (mode == "large") cout << "510510 1000000\n";
    else {
        ll n = 2 * (1 + rand() % 15);
        ll m = 100 + rand() % 500;
        cout << n << " " << m << "\n";
    }
}
