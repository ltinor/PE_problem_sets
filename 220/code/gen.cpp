#include<bits/stdc++.h>
using namespace std;
#define ll long long

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];
    
    int n;
    ll K;
    if (mode == "small") {
        n = rand_int(1, 10);
        ll maxK = (1LL << n);
        K = rand_int(0, (int)min(maxK, 1000LL));
    } else {
        n = rand_int(11, 30);
        ll maxK = (1LL << n);
        K = rand_int(0, (int)min(maxK, 100000LL));
    }
    
    cout << n << " " << K << "\n";
}
