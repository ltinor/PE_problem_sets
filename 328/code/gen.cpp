// PE 328 - Test case generator
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];
    
    int N;
    if (mode == "small") N = 1 + rand() % 20;
    else if (mode == "medium") N = 20 + rand() % 200;
    else N = 200 + rand() % 5000;
    cout << N << "\n";
}
