// PE 329 - Test case generator
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];
    
    int L;
    if (mode == "small") L = 3 + rand() % 5;
    else L = 6 + rand() % 10;
    
    string seq;
    for (int i = 0; i < L; i++)
        seq += (rand() % 2 == 0 ? 'P' : 'N');
    cout << seq << "\n";
}
