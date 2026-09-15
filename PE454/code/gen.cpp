#include<bits/stdc++.h>
using namespace std;
using ll = long long;
ll rand_ll(ll l, ll r) { return l + (ll)rand()*rand() % (r-l+1); }
int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small"; if (argc > 1) mode = argv[1];
    ll L;
    if (mode == "small") L = rand_ll(3, 30);
    else if (mode == "large") L = rand_ll(31, 500);
    else L = atoll(argv[1]);
    cout << L << "\n";
}
