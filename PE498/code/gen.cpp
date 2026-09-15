#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];

    if (mode == "small") {
        cout << "5 10 1000\n";  // n=5, d=10, mod=1000
    } else if (mode == "large") {
        cout << "PE\n";
    } else {
        cout << mode << "\n";
    }
}
