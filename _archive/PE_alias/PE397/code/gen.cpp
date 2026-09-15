#include<bits/stdc++.h>
using namespace std;
using ll = long long;
ll rand_ll(ll l, ll r) { return l + (ll)rand()*rand() % (r-l+1); }
int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small"; if (argc > 1) mode = argv[1];
    ll K, X;
    if (mode == "small") { K = rand_ll(1, 5); X = rand_ll(3, 10); }
    else if (mode == "large") { K = rand_ll(10, 100); X = rand_ll(50, 200); }
    else { K = rand_ll(1, 3); X = rand_ll(3, 8); }
    cout << K << " " << X << "\n";
}
