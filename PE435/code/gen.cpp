#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small"; if (argc > 1) mode = argv[1];
    if (mode == "pe") cout << "pe\n";
    else if (mode == "large") cout << "test " << 1000000 << " " << 10 << "\n";
    else {
        ll n = 1 + rand() % 20;
        ll x = rand() % 5;
        cout << "test " << n << " " << x << "\n";
    }
}
