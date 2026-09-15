#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll rand_ll(ll l, ll r){
    return l + (ll)rand() * rand() % (r - l + 1);
}

int main(int argc, char* argv[]){
    srand(time(0));
    string mode = "small";
    if(argc > 1) mode = argv[1];
    
    ll K;
    if(mode == "small"){
        K = rand_ll(10, 500);
    } else {
        K = rand_ll(1000, 10000);
    }
    
    cout << K << "\n";
}
