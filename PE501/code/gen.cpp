#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];

    if (mode == "small") {
        cout << "100\n";
    } else if (mode == "large") {
        cout << "1000000\n";
    } else if (mode == "PE") {
        cout << "PE\n";
    } else {
        cout << mode << "\n";
    }
}
