#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int rand_int(int l, int r){
    return l + rand() % (r - l + 1);
}

ll rand_ll(ll l, ll r){
    return l + (ll)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]){
    srand(time(0));

    string mode = "small";
    if(argc > 1) mode = argv[1];

    int n;
    ll m;

    if(mode == "small"){
        n = rand_int(5, 20);
        m = rand_ll(100, 1000000);
    } else {
        n = rand_int(10, 100);
        m = rand_ll(1000000, 1000000000000LL);
    }

    assert(n >= 2 && n <= 100);
    assert(m >= 1 && m <= 1000000000000LL);

    cout << n << " " << m << "\n";
}
