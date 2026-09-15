#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small"; if (argc > 1) mode = argv[1];
    ll m = 1, n = 3;
    if (mode == "pe") { m = 10; n = 1000000000000LL; }
    else if (mode == "large") { m = 2; n = 3; }
    else { n = atoll(argv[1]); if (argc > 2) m = atoll(argv[2]); }
    cout << m << " " << n << "\n";
}
