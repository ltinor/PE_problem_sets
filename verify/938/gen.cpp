#include<bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    srand((unsigned)time(0));
    int lo = 1, hi = 30;
    if (argc > 1) { string m = argv[1]; if (m == "small") { lo = 1; hi = 30; } else if (m == "large") { lo = 100; hi = 200; } }
    int R = lo + rand() % (hi - lo + 1);
    int B = lo + rand() % (hi - lo + 1);
    cout << R << " " << B << "\n";
    return 0;
}
