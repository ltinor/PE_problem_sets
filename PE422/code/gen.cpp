#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small"; if (argc > 1) mode = argv[1];
    ll n;
    if (mode == "pe") n = 1;
    else { n = atoll(argv[1]); if (n <= 0) n = 7; }
    cout << n << "\n";
}
