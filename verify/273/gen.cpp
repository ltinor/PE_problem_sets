#include <bits/stdc++.h>
using namespace std;
int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];
    int lim;
    if (mode == "small") lim = 40 + rand() % 30;
    else if (mode == "large") lim = 100 + rand() % 50;
    else lim = stoi(mode);
    cout << lim << "\n";
    return 0;
}
