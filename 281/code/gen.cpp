#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];
    
    ll T;
    if (mode == "small") {
        T = rand() % 10 + 1;  // T = 1..10
    } else if (mode == "pe") {
        T = 1000000000000000LL; // 10^15
    } else {
        T = rand() % 50 + 1;
    }
    
    cout << T << "\n";
}
