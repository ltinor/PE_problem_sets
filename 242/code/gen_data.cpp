#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll rand_ll(ll l, ll r) {
    return l + (ll)(rand()) * (ll)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<ll> test_cases(10);

    test_cases[0] = 10;  // sample

    for (int i = 1; i < 3; i++)
        test_cases[i] = rand_ll(10, 100);

    for (int i = 3; i < 5; i++)
        test_cases[i] = rand_ll(100, 100000);

    for (int i = 5; i < 7; i++)
        test_cases[i] = rand_ll(100000, 100000000);

    test_cases[7] = 1;  // edge

    for (int i = 8; i < 10; i++)
        test_cases[i] = rand_ll(100000000, 1000000000000LL);

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with N = " << test_cases[i] << "\n";
    }

    return 0;
}
