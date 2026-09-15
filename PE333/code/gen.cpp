#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll rand_ll(ll l, ll r) { return l + (ll)rand() * rand() % (r - l + 1); }

int main(int argc, char* argv[]) {
    srand(time(0));
    string mode = "small";
    if (argc > 1) mode = argv[1];
    int N;
    if (mode == "small") N = rand_ll(50, 200);
    else if (mode == "large") N = rand_ll(500, 2000);
    else N = atoi(argv[1]);
    cout << N << "\n";
}
