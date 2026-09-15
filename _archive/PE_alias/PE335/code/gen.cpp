#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll rand_ll(ll l, ll r) { return l + (ll)rand() * rand() % (r - l + 1); }

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];
    int x;
    if (mode == "small") x = rand_ll(2, 20);
    else if (mode == "large") x = rand_ll(50, 200);
    else x = atoi(argv[1]);
    cout << x << "\n";
}
