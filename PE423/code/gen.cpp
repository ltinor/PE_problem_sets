#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small"; if (argc > 1) mode = argv[1];
    ll L;
    if (mode == "pe") L = 50000000;
    else if (mode == "large") L = 50;
    else { L = atoll(argv[1]); if (L <= 0) L = 10; }
    cout << L << "\n";
}
