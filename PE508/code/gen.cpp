#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];
    if (mode == "small") {
        ll l = rand() % 10 + 1;
        cout << l << "\n";
    } else cout << mode << "\n";
}
