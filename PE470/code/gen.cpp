#include<bits/stdc++.h>
using namespace std;
using ll = long long;
ll rand_ll(ll l, ll r) { return l + (ll)rand()*rand() % (r-l+1); }
int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small"; if (argc > 1) mode = argv[1];
    int d, c;
    if (mode == "small") {
        d = rand_ll(4, 6);
        c = rand_ll(0, 5);
    } else if (mode == "large") {
        d = rand_ll(7, 15);
        c = rand_ll(0, 10);
    } else {
        d = atoi(argv[1]);
        c = atoi(argv[2]);
    }
    cout << d << " " << c << "\n";
}
