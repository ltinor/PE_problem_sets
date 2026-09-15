#include<bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];

    int n;
    if (mode == "small") {
        n = rand() % 5 + 1;
    } else {
        n = rand() % 5 + 5;
    }

    cout << n << "\n";
    return 0;
}
