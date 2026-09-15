// PE 330 - Test case generator
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];
    
    int N;
    if (mode == "small") N = rand() % 10;
    else if (mode == "medium") N = 10 + rand() % 100;
    else N = 100 + rand() % 500;
    cout << N << "\n";
}
