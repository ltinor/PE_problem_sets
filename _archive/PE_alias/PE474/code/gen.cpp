#include<bits/stdc++.h>
using namespace std;
using ll = long long;
ll rand_ll(ll l, ll r) { return l + (ll)rand()*rand() % (r-l+1); }
int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small"; if (argc > 1) mode = argv[1];
    ll N, D;
    if (mode == "small") { N = rand_ll(1, 8); D = rand_ll(1, 99); }
    else if (mode == "large") { N = rand_ll(9, 12); D = rand_ll(1, 999); }
    else { N = atoll(argv[1]); D = atoll(argv[2]); }
    cout << N << " " << D << "\n";
}
