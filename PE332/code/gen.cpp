#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll rand_ll(ll l, ll r) { return l + (ll)rand() * rand() % (r - l + 1); }

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];
    int R;
    if (mode == "small") R = rand_ll(1, 10);
    else if (mode == "large") R = rand_ll(11, 25);
    else R = atoi(argv[1]);
    cout << R << "\n";
}
