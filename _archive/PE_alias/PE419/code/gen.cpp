#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small"; if (argc > 1) mode = argv[1];
    ll N;
    if (mode == "pe") N = 1000000000000LL;
    else if (mode == "large") N = 40;
    else { N = atoll(argv[1]); if (N <= 0) N = 5; }
    cout << N << "\n";
}
