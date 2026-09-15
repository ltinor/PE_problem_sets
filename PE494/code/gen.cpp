#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];

    if (mode == "small") {
        cout << "3 100\n";  // K=3, N=100
    } else if (mode == "large") {
        cout << "PE\n";
    } else {
        cout << mode << "\n";
    }
}
