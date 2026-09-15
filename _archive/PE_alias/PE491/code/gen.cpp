#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];

    if (mode == "small") {
        cout << "4\n";  // 4-digit double pandigital (digits 0,1 each twice)
    } else if (mode == "large") {
        cout << "20\n";  // PE case
    } else {
        cout << mode << "\n";
    }
}
