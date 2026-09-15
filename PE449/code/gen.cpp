#include<bits/stdc++.h>
using namespace std;
using ll = long long;
ll rand_ll(ll l, ll r) { return l + (ll)rand()*rand() % (r-l+1); }
int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small"; if (argc > 1) mode = argv[1];
    ll a;
    if (mode == "small") a = rand_ll(1, 5);
    else a = rand_ll(6, 20);
    cout << a << "\n";
}
