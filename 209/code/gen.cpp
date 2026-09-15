#include<bits/stdc++.h>
using namespace std;

// PE 209: Generator for checking

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    int k;
    if (mode == "small") {
        k = rand() % 3 + 1; // 1, 2, 3
    } else if (mode == "pe") {
        k = 6;
    } else {
        k = rand() % 5 + 1; // 1-5
    }

    cout << k << "\n";
}
