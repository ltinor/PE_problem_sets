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

    int Kmax;

    if(mode == "small"){
        Kmax = rand_ll(2, 100);
    } else {
        Kmax = rand_ll(2, 12000);
    }

    assert(Kmax >= 2 && Kmax <= 12000);
    cout << Kmax << "\n";
}
