#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll rand_ll(ll l, ll r) {
    return l + (ll)(rand()) * (ll)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<int> test_cases(10);

    // 1: PE original (100 players)
    test_cases[0] = 100;

    // 2-3: tiny
    test_cases[1] = 2;
    test_cases[2] = 4;

    // 4-5: small
    test_cases[3] = 10;
    test_cases[4] = 20;

    // 6-7: medium
    test_cases[5] = 50;
    test_cases[6] = 200;

    // 8-9: larger
    test_cases[7] = (int)rand_ll(25, 75) * 2;
    test_cases[8] = 500;

    // 10: random even
    test_cases[9] = (int)rand_ll(5, 150) * 2;

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i] << "\n";
        fout.close();
        cout << "Generated " << filename << " with N = " << test_cases[i] << "\n";
    }

    return 0;
}
