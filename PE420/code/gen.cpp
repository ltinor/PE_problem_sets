#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small"; if (argc > 1) mode = argv[1];
    ll N;
    if (mode == "pe") N = 10000000;
    else if (mode == "large") N = 1000;
    else { N = atoll(argv[1]); if (N <= 0) N = 50; }
    cout << N << "\n";
}
