#include<bits/stdc++.h>
using namespace std;
using ll = long long;
ll rand_ll(ll l, ll r) { return l + (ll)rand()*rand() % (r-l+1); }
int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small"; if (argc > 1) mode = argv[1];
    int k, N;
    if (mode == "small") {
        k = rand_ll(1, 3);
        N = rand_ll(1, 10);
    } else {
        k = rand_ll(2, 5);
        N = rand_ll(11, 50);
    }
    cout << k << " " << N << "\n";
}
