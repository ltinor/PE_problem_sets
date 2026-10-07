#include<bits/stdc++.h>
using namespace std;
#define ll long long

int rand_int(int l, int r) {
    return l + rand() % (r - l + 1);
}

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];
    
    ll C;
    if (mode == "small") {
        C = rand_int(1, 10000);
    } else {
        C = rand_int(10001, 1000000000);
    }
    
    cout << C << "\n";
}
