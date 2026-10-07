#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];
    
    ll R;
    if (mode == "small") {
        R = rand() % 5 + 1;  // 1..5
    } else if (mode == "pe") {
        R = 1000;
    } else {
        R = rand() % 50 + 1;
    }
    cout << R << "\n";
}
