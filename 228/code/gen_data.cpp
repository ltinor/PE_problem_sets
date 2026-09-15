#include<bits/stdc++.h>
using namespace std;
#define ll long long

ll rand_ll(ll l, ll r) {
    return l + (ll)(rand()) * (ll)(rand()) % (r - l + 1);
}

int main() {
    system("mkdir -p data");
    srand(time(0));

    vector<pair<int,int>> test_cases(10);

    // 1: PE original
    test_cases[0] = {1864, 1909};

    // 2-3: tiny single polygon
    test_cases[1] = {3, 3};
    test_cases[2] = {4, 4};

    // 4-5: small range
    test_cases[3] = {3, 4};
    test_cases[4] = {5, 7};

    // 6-7: medium
    test_cases[5] = {10, 15};
    test_cases[6] = {20, 25};

    // 8-9: small range at higher values
    test_cases[7] = {50, 52};
    test_cases[8] = {100, 105};

    // 10: random
    test_cases[9] = {(int)rand_ll(5, 30), (int)rand_ll(31, 50)};

    for (int i = 0; i < 10; i++) {
        string filename = string("data/") + (i < 9 ? "0" : "") + to_string(i + 1) + ".in";
        ofstream fout(filename);
        fout << test_cases[i].first << " " << test_cases[i].second << "\n";
        fout.close();
        cout << "Generated " << filename << " with L=" << test_cases[i].first
             << " R=" << test_cases[i].second << "\n";
    }

    return 0;
}
