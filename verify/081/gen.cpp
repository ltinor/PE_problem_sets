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

    int N;
    if(mode == "small"){
        N = rand_ll(2, 8);
    } else if(mode == "large"){
        N = rand_ll(40, 80);
    } else {
        N = 5;
    }

    cout << N << "\n";
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << rand_ll(1, 9999);
            if(j < N - 1) cout << " ";
        }
        cout << "\n";
    }

    return 0;
}
