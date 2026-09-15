#include<bits/stdc++.h>
using namespace std;
using ll = long long;
ll rand_ll(ll l, ll r) { return l + (ll)rand()*rand() % (r-l+1); }
int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small"; if (argc > 1) mode = argv[1];
    int n;
    if (mode == "small") n = rand_ll(3, 12);
    else if (mode == "large") n = rand_ll(13, 100);
    else n = atoi(argv[1]);
    cout << n << "\n";
}
