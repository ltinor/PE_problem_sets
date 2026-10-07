#include<bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];
    
    if (mode == "small") {
        cout << rand() % 10 + 1 << "\n";
    } else {
        cout << "1\n";
    }
}
