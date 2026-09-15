#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll rand_ll(ll l, ll r) {
    return l + (ll)rand() * rand() % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<ll> cases(10);

    // 1. sample (N=10)
    cases[0] = 10;

    // 2-3. small (N <= 100)
    for (int i = 1; i < 3; i++)
        cases[i] = rand_ll(3, 100);

    // 4-6. medium/large
    cases[3] = 1000;
    cases[4] = 100000;
    cases[5] = 5000000;

    // 7. boundary: N=3 (smallest perimeter for a triangle)
    cases[6] = 3;

    // 8. PE answer value
    cases[7] = 10000000;

    // 9-10. random
    for (int i = 8; i < 10; i++)
        cases[i] = rand_ll(1000, 2000000);

    for (int i = 0; i < 10; i++) {
        string fname = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(fname);
        fout << cases[i] << "\n";
        fout.close();
        cout << "Generated " << fname << " N=" << cases[i] << "\n";
    }
    return 0;
}
