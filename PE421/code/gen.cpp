#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small"; if (argc > 1) mode = argv[1];
    ll N, M;
    if (mode == "pe") { N = 100000000000LL; M = 100000000; }
    else if (mode == "large") { N = 500; M = 500; }
    else {
        N = (argc > 1) ? atoll(argv[1]) : 0;
        M = (argc > 2) ? atoll(argv[2]) : 0;
        if (N <= 0) N = 10;
        if (M <= 0) M = 100;
    }
    cout << N << " " << M << "\n";
}
