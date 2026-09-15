#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll rand_ll(ll l, ll r){
    return l + (ll)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]){
    srand(time(0));

    string mode = "small";
    if(argc > 1) mode = argv[1];

    ll b;

    if(mode == "small"){
        // Small b for brute: b ≤ 200 → n ≤ 101
        do {
            b = rand_ll(3, 200);
        } while((b + 3) % 2 != 0); // b must be odd
    } else {
        b = rand_ll(1000000, 12017639147LL);
        if((b + 3) % 2 != 0) b++; // ensure odd
    }

    cout << b << "\n";
}
