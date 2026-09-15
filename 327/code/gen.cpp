// PE 327 - Test case generator
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];
    
    int Cmax, R;
    if (mode == "small") {
        Cmax = 3 + rand() % 3;  // 3-5
        R = 1 + rand() % 5;      // 1-5
    } else if (mode == "medium") {
        Cmax = 4 + rand() % 4;   // 4-7
        R = 3 + rand() % 5;      // 3-7
    } else {
        Cmax = 5 + rand() % 10;  // 5-14
        R = 5 + rand() % 10;     // 5-14
    }
    cout << Cmax << " " << R << "\n";
}
