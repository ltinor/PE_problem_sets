#include<bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];

    int P;
    if (mode == "small") {
        P = rand() % 50 + 1;
    } else {
        P = rand() % 500 + 50;
    }

    cout << P << "\n";
    return 0;
}
