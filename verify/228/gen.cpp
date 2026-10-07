#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll rand_ll(ll l, ll r) {
    return l + (ll)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    int L, R;
    if (mode == "small") {
        L = (int)rand_ll(3, 10);
        R = L + (int)rand_ll(0, 5);
    } else if (mode == "large") {
        L = (int)rand_ll(10, 50);
        R = L + (int)rand_ll(5, 20);
    }

    cout << L << " " << R << "\n";
    return 0;
}
