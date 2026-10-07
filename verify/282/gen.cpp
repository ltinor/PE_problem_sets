#include<bits/stdc++.h>
using namespace std;
using ll = long long;

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];
    
    int m;
    ll n, M;
    if (mode == "small") {
        m = rand() % 4; // 0..3
        n = rand() % 10;
        M = rand() % 1000 + 1;
    } else if (mode == "pe") {
        // simulate PE: sum A(n,n) for n=0..6 mod 14^8
        // This doesn't fit single input, so just test one
        m = 3; n = 6; M = 1475789056LL;
    } else {
        m = rand() % 4;
        n = rand() % 100;
        M = rand() % 1000000 + 1;
    }
    cout << m << " " << n << " " << M << "\n";
}
