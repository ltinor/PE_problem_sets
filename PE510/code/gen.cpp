#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];
    if (mode == "small") {
        ll n = rand() % 20 + 5;
        cout << n << "\n";
    } else cout << mode << "\n";
}
