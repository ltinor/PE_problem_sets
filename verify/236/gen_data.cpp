#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll rand_ll(ll l, ll r) {
    return l + (ll)(rand()) * (ll)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    // 10 test cases
    struct TC { ll a[5], b[5]; };
    vector<TC> cases(10);

    // Case 1: PE data (sample)
    cases[0] = {{5248, 1312, 2624, 5760, 3936}, {640, 1888, 3776, 3776, 5664}};

    // Cases 2-3: tiny random (a_i, b_i <= 5)
    for (int c = 1; c <= 2; c++) {
        for (int i = 0; i < 5; i++) {
            cases[c].a[i] = rand_ll(1, 5);
            cases[c].b[i] = rand_ll(1, 5);
        }
    }

    // Cases 4-6: small random (a_i, b_i <= 20)
    for (int c = 3; c <= 5; c++) {
        for (int i = 0; i < 5; i++) {
            cases[c].a[i] = rand_ll(1, 20);
            cases[c].b[i] = rand_ll(1, 20);
        }
    }

    // Cases 7-8: PE scale data with modified numbers
    for (int c = 6; c <= 7; c++) {
        for (int i = 0; i < 5; i++) {
            cases[c].a[i] = cases[0].a[i] / 8;
            cases[c].b[i] = cases[0].b[i] / 8;
        }
    }

    // Case 9: all equal
    for (int i = 0; i < 5; i++) {
        cases[8].a[i] = 10;
        cases[8].b[i] = 10;
    }

    // Case 10: scaled down PE
    int div = 16;
    for (int i = 0; i < 5; i++) {
        cases[9].a[i] = cases[0].a[i] / div;
        cases[9].b[i] = cases[0].b[i] / div;
    }

    for (int c = 0; c < 10; c++) {
        string fname = string("data/") + (c < 9 ? "0" : "") + to_string(c + 1) + ".in";
        ofstream f(fname);
        for (int i = 0; i < 5; i++) {
            f << cases[c].a[i] << " " << cases[c].b[i] << "\n";
        }
        f.close();
        cout << "Generated " << fname << "\n";
    }

    return 0;
}
