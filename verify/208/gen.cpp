#include<bits/stdc++.h>
using namespace std;

// PE 208: Generator for checking

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    int n;
    if (mode == "small") {
        n = (rand() % 4 + 1) * 5; // 5, 10, 15, 20
    } else if (mode == "pe") {
        n = 70;
    } else {
        n = (rand() % 10 + 1) * 5; // 5 to 50
    }

    cout << n << "\n";
}
