#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll rand_ll(ll l, ll r) {
    return l + (ll)rand() * rand() % (r - l + 1);
}

string rand_digits(int len) {
    string s;
    for (int i = 0; i < len; i++)
        s += (char)('0' + rand() % 10);
    return s;
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string mode = "small";
    if (argc > 1) mode = argv[1];

    string A, B;
    ll n;

    if (mode == "small") {
        A = rand_digits(3);
        B = rand_digits(4);
        n = rand_ll(1, 30);
    } else if (mode == "large") {
        A = rand_digits(10);
        B = rand_digits(10);
        n = rand_ll(1, 1000);
    }

    cout << A << "\n" << B << "\n" << n << "\n";
    return 0;
}
